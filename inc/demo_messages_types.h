#define DEMO_DATA_IND(mSGpTR) (mSGpTR)->ittiMsg.message_demo
typedef struct message_demo_s {
	const char *name;
	const char *university;
} message_demo_t;