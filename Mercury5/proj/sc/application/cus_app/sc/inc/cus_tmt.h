
#include "remote.ho"


u32		cusTmt_getNbTasks(void);
u32		cusTmt_getNbMboxs(void);

bool	cusTmt_getTask(StatusElt_t * pElt, u32 taskIdx);
bool	cusTmt_getMbox(StatusElt_t * pElt, u32 mboxIdx);
