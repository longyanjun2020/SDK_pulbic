/*
*********************************************************************************************************
*                         AIT Multimedia Network -- HTTP Server
*                     (c) Copyright 2012, Alpha Imaging Technology Corp.
*               All rights reserved. Protected by international copyright laws.
*********************************************************************************************************
*
* Description:
*
*/
#define STRUCT_SESSION_PROPERTY   struct user_session_t user
#include "amn_cgi.h"

static struct cgi_handler_t *cgi = NULL;

// testcase: /cgi-bin/User.cgi?action=login&user=admin&pass=admin
// testcase: /cgi-bin/User.cgi?action=logout
// testcase: /cgi-bin/User.cgi?action=add&user=bernard&pass=1234&class=ADMIN
// testcase: /cgi-bin/User.cgi?action=mod&user=bernard&opass=1234&npass=5566
// testcase: /cgi-bin/User.cgi?action=del&user=bernard
//*******************************************************************************************************
static int identify_config_users(char **uname, char **upass, char **uclass)
{
    char *old_uname;
    int k, i;

    k = amn_currConfig_get("User.Account.Totals")->v.intVal;
    for (i=1; i <= k; i++) {
        old_uname = amn_currConfig_get_enum( "User.Account.%d.Username", i ) -> v.strVal;
        if ( !strcmp( *uname, old_uname ) ) {
            *uname = old_uname;

            *upass  = amn_currConfig_get_enum( "User.Account.%d.Password", i ) -> v.strVal;
            *uclass = amn_currConfig_get_enum( "User.Account.%d.Class", i ) -> v.strVal;
            return i;
        }
    }
    return -1;
}

static void change_config_user(int i, char *uname, char *upass, char *uclass)
{
    amn_currConfig_set_enum( "User.Account.%d.Username", i, uname );
    amn_currConfig_set_enum( "User.Account.%d.Password", i, upass );
    amn_currConfig_set_enum( "User.Account.%d.Class", i, uclass );
}

static void delete_config_user(int i)
{
    int j, k;
    char *uname, *upass, *uclass;

    k = amn_currConfig_get("User.Account.Totals")->v.intVal;
    for (j=i; j<k; j++) {
        // move the <j+1>'th user slot to <j>'th
        uname  = amn_currConfig_get_enum( "User.Account.%d.Username", j+1 )->v.strVal;
        upass  = amn_currConfig_get_enum( "User.Account.%d.Password", j+1 )->v.strVal;
        uclass = amn_currConfig_get_enum( "User.Account.%d.Class", j+1 )->v.strVal;

        amn_currConfig_set_enum( "User.Account.%d.Username", j, uname );
        amn_currConfig_set_enum( "User.Account.%d.Password", j, upass );
        amn_currConfig_set_enum( "User.Account.%d.Class", j, uclass );
    }

    amn_currConfig_iset( "User.Account.Totals", k - 1 );
}

char *create_user_session( struct cgi_virt_file_t *f, char *uname, char *upass, char *uclass )
{
    char *extra_head = http_create_session( f );
    struct user_session_t* user_sess;

    user_sess = (struct user_session_t*) f->sess;

    user_sess->uname = uname;
    user_sess->upass = upass;
    user_sess->uclass = USER_CLASS__NOBODY;
    if      (!strcmp(uclass, "ADMIN"))   user_sess->uclass = USER_CLASS__ADMIN;
    else if (!strcmp(uclass, "USER"))    user_sess->uclass = USER_CLASS__USER;
    else if (!strcmp(uclass, "GUEST"))   user_sess->uclass = USER_CLASS__GUEST;

    return extra_head;
}

// load user session && check user authority
int load_check_user( struct cgi_virt_file_t *f, int _class, char **sname, char **spass, char **extra_head )
{
    char *head = http_load_session(f);
    struct user_session_t* user_sess;

    user_sess = (struct user_session_t*) f->sess;
    if (head == NULL)
        return VHAND_ERR__REQUIRE_AUTHENTICATION;
    if (extra_head)
        *extra_head = head;

    *sname  = user_sess->uname;
    *spass  = user_sess->upass;
    if (user_sess->uclass <= _class)  return VHAND_OK__AUTHORIZED;
    else                              return VHAND_ERR__NO_AUTHORITY;
}


//*******************************************************************************************************
static int cgi_processs_actions(IN struct cgi_virt_file_t *f, OUT char *buf, IN int maxlen, char **extra_head, int *auth)
{
    struct cgi_param_t *prmUser = NULL, *prmPass, *prmNPass, *prmOPass, *prmClass;
    int  i = -1;
    char *uname = NULL, *upass = NULL, *uclass = NULL;   // user info from URL parameters
    char *sname, *spass;            // user info from the cookie session
    char *ptr = buf;
    int  resp_code = CGI_ERR__OK;

    #define exit_with_response(_res)  do { \
        resp_code = _res; \
        goto L_exit_simple_response; \
    } while (0)

    #define __load_check_user( _class ) do { \
        *auth = load_check_user( f, _class, &sname, &spass, extra_head ); \
        if (*auth < 0) { \
            exit_with_response( *auth - VHAND_ERR__REQUIRE_AUTHENTICATION + CGI_ERR__REQUIRE_AUTHEN ); \
        } \
    } while (0)

    switch(cgi_get_state(f)) {
    case CGI_ACTSTATE__EOF:
        if (!buf)  cgi_set_state( f, CGI_ACTSTATE__START );      // after DRY-RUN, we are ready for REAL-RUN
        return 0;  // EOF

    case CGI_ACTSTATE__NOT_READY:
        *auth = VHAND_ERR__ILLEGAL_URL_PARAM;
        return 0;  // no URL's param in the HTTP-GET/POST request

    default:
    case CGI_ACTSTATE__START:
        *auth = VHAND_ERR__ILLEGAL_URL_PARAM;

        // get the common Param: "user"
        switch(cgi_get_action(f)) {
        case CGI_ACTION_ADD:
        case CGI_ACTION_DEL:
            __load_check_user(USER_CLASS__ADMIN);
            goto L_get_URL_params;

        case CGI_ACTION_MOD:
            __load_check_user(USER_CLASS__USER);
            goto L_get_URL_params;
        case CGI_ACTION_LOGIN:
L_get_URL_params:
            prmUser = cgi_param_nget( f, "user" );
            if (!prmUser)
                exit_with_response( CGI_ERR__MISS_PARAM );

            uname = prmUser->value;
            i = identify_config_users( &uname, &upass, &uclass );
            if (cgi_get_action(f) == CGI_ACTION_ADD) {
                if (i >= 0) {
                    if (buf) osal_dprint(VERBOSE, "USER.CGI: duplicate %d'th user '%s'", i, prmUser->value);
                    exit_with_response( CGI_ERR__ILL_USER );
                }
            }
            else {
                if (i < 0) {
                    if (buf) osal_dprint(VERBOSE, "USER.CGI: non-existing the user '%s'", prmUser->value);
                    exit_with_response( CGI_ERR__ILL_USER );
                }
            }
            break;

        case CGI_ACTION_LOGOUT:
            __load_check_user(USER_CLASS__NOBODY);
            break;

        default:
            resp_code = cgi_get_error(f);
            if (resp_code != 0)
                goto L_exit_simple_response;
            exit_with_response( CGI_ERR__INTERNAL_ERROR );
        }

        // now actual process the CGI action
        switch(cgi_get_action(f)) {
        case CGI_ACTION_LOGIN:
            prmPass = cgi_param_nget( f, "pass" );
            if (!prmPass)
                exit_with_response( CGI_ERR__MISS_PARAM );
            if ( strcmp(prmPass->value, upass) )
                exit_with_response( CGI_ERR__ERR_PASS );

            if (!buf) {
                *extra_head = create_user_session( f, uname, upass, uclass );
                osal_dprint(VERBOSE, "USER.CGI: Login user=%s class=%s,  sess=%s",
                            uname, uclass, f->sess->id);
            }
            *auth = VHAND_OK__AUTHENTICATOR;
            break;

        case CGI_ACTION_LOGOUT:
            if (buf) {
                session_destroy( f->sess, "LOGOUT" );
                osal_dprint(VERBOSE, "USER.CGI: Logout user=%s", sname);
            }
            *auth = VHAND_OK__AUTHORIZED;
            break;

        case CGI_ACTION_ADD:
            prmPass = cgi_param_nget( f, "pass" );
            if (!prmPass)
                exit_with_response( CGI_ERR__MISS_PARAM );

            uclass = "USER";
            prmClass = cgi_param_nget( f, "class" );
            if (prmClass)  uclass=prmClass->value;

            // Now perform the ADD action
            if (buf) {
                i = amn_currConfig_get("User.Account.Totals")->v.intVal + 1;
                amn_currConfig_iset("User.Account.Totals", i);
                change_config_user( i, prmUser->value, prmPass->value, uclass );
                osal_dprint(VERBOSE, "USER.CGI: ADD new USER (%s, %s), by %s. Totals=%d",
                            prmUser->value, uclass, sname, i);
            }
            *auth = VHAND_OK__AUTHORIZED;
            break;

        case CGI_ACTION_MOD:
            if (((struct user_session_t*)f->sess)->uclass <= USER_CLASS__ADMIN) {
                // change user by the admin:    action=mod&user=bernard&pass=1234&class=USER
                prmPass = cgi_param_nget( f, "pass" );
                if (prmPass)  upass = prmPass->value;

                prmClass = cgi_param_nget( f, "class" );
                if (prmClass)  uclass=prmClass->value;
            }
            else {
                // change user's own password:  action=mod&user=bernard&opass=1234&npass=5566
                if ( strcmp(uname,sname) ) {
                    osal_dprint(VERBOSE, "USER.CGI: no authority !! MOD USER %s by %s", uname, sname);
                    *auth = VHAND_ERR__NO_AUTHORITY;
                    exit_with_response( CGI_ERR__NO_AUTHOR );
                }

                *auth = VHAND_ERR__ILLEGAL_URL_PARAM;
                prmOPass = cgi_param_nget( f, "opass" );
                if (!prmOPass)
                    exit_with_response( CGI_ERR__MISS_PARAM );
                if ( strcmp(prmOPass->value, upass) )
                    exit_with_response( CGI_ERR__ERR_PASS );

                prmNPass = cgi_param_nget( f, "npass" );
                if (!prmNPass)
                    exit_with_response( CGI_ERR__MISS_PARAM );

                upass = prmNPass->value;
            }

            // Now perform the MOD action
            if (buf) {
                change_config_user( i, uname, upass, uclass );
                osal_dprint(VERBOSE, "USER.CGI: MOD USER (%s, %s), by %s", uname, uclass, sname);
            }
            *auth = VHAND_OK__AUTHORIZED;
            break;

        case CGI_ACTION_DEL:
            if (buf) {
                delete_config_user( i );
                osal_dprint(VERBOSE, "USER.CGI: DEL USER (%s, %s), by %s", uname, uclass, sname);
            }
            *auth = VHAND_OK__AUTHORIZED;
            break;
        }
    }

L_exit_simple_response:
    CGI_PRINTF( buf, ptr, maxlen, "%d\n%s\n", resp_code, cgi_err_text(resp_code) );
    cgi_set_state( f, CGI_ACTSTATE__EOF );
    return ptr - buf;
}



//*******************************************************************************************************
static int web_get_info( struct cgi_handler_t *h, const char *filename, char **extra_head, struct File_Info *info)
{
    enum vhand_authen_spec_t auth;
    int len = 0, n;
    cgi_action_prepare( h->curr_file );

    while ((n=cgi_processs_actions( h->curr_file, NULL, 1024, extra_head, (int*)&auth )) != 0)
        len += n;

    if (len > 0)
        info->file_length = len;
    else
        info->file_length = UPNP_USING_CHUNKED;
#if 0
    info->file_length = 1000;
    info->file_length = UPNP_INFINITE;
    info->file_length = UPNP_USING_CHUNKED;
    info->file_length = UPNP_UNTIL_CLOSE;
#endif

    info->last_modified = 1362641224; // Thu Mar 7 15:27:04 CST 2013
    info->is_directory = 0;
    info->is_readable = 1;
    info->content_type = osal_strdup("text/plain");  // will be free'd
    return auth;
}

static int web_open( struct cgi_virt_file_t *f )
{
    return 0;
}

static int web_read(IN struct cgi_virt_file_t *f)
{
    int auth;
    int len = 0, n = 0;
    char *buf = f->web_rwbuf;

    while ( ( (n = cgi_processs_actions( f, buf + len, f->web_rwlen, NULL, &auth )) != 0 ) && (len < f->web_rwlen) )
        len += n;

    return len;
}

static int web_write(IN struct cgi_virt_file_t *f)
{
    return 0;
}

static int web_seek(IN struct cgi_virt_file_t *f, IN int offset, IN int whence)
{
    return 0;
}

static int web_close( IN struct cgi_virt_file_t *f)
{
    return 0;
}

//*******************************************************************************************************
static struct cgi_file_operations_t cgi_cb = { web_get_info, web_open, web_read, web_write, web_seek, web_close };

void init_user_cgi(void)
{
    if (cgi) return;  // already initialized before
    cgi = register_vdir_handlers( "/cgi-bin/User.cgi", &cgi_cb );
}

