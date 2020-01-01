#ifndef DVM_ALARM_HEADER__
#define DVM_ALARM_HEADER__

#ifdef __cplusplus
extern "C" {
#endif

#define E_ALARM_OK           (0)
#define E_ALARM_FAILED       (-1)
#define E_ALARM_NOTFOUND     (-2)
#define E_ALARM_OUTOFMEM     (-4)
#define E_ALARM_AGAIN        (-11)
#define E_ALARM_WOULDBLOCK   E_ALARM_AGAIN
#define E_ALARM_UNSUPPORT    (-200)
#define E_ALARM_NOIMPL       (-201)

/*
 * register an push alarm entry at scheduled point.
 * @param schedulePoint the millies  since AD 1970, Jan 1, 0: 0:0, UTC
 * @param suite the suite id string
 * @param the 1-based midlet id of the midlet to be launched at scheduled time
 *
 * @return E_ALARM_OK on success, otherwise no-zero negative error code
 */
int dvm_alarm_push_register(long long schedulePoint, const char *suite, int midletId);

/*
 * unregister an previously push alarm at scheduled point by specified suite/midletId.
 *
 * @param schedulePoint the millies  since AD 1970, Jan 1, 0: 0:0, UTC
 * @param suite the suite id string
 * @param mdiletId the midlet id
 *
 * @return E_ALARM_OK on success, otherwise non-zero negative error code
 */
int dvm_alarm_push_unregister(long long schedulePoint, const char *suite, int midletId);

/*
 * @return TRUE if the alarm has been availablei.
 *         FALSE if the push alarm entry hadn't been fired.
 */
int dvm_alarm_push_avail(long long schedulePoint);

int dvm_alarm_push_init(void);

int dvm_alarm_push_finalize(void);

#ifdef __cplusplus
}
#endif

#endif
