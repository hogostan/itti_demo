#include "intertask_interface.h"
#include "assertions.h"
#include "intertask_interface_init.h"
void * demo_receiver_thread(__attribute__((unused)) void *args)
{
	itti_mark_task_ready (TASK_DEMO_RECEIVER);
	while (1) {
		printf("in receiving message----\n");
		MessageDef *received_message_p = NULL;
		// void itti_receiver_msg(task_id_t task_id, MessageDef **rx_msg);
		itti_receive_msg (TASK_DEMO_RECEIVER, &received_message_p);
		DevAssert (received_message_p != NULL);
		// #define ITTI_MSG_ID(mSGpTR) ((mSGpTR)->ittiMsgHeader.messageId)
		switch (ITTI_MSG_ID (received_message_p)) {
			case MESSAGE_DEMO:
				printf("TASK_DEMO_RECEIVER received a MESSAGE_DEMO\n This demo will exit in 3 seconds.\n");
				break;
			default:
				printf("TASK_DEMO_RECEIVER received a unknown message\n");
		}
		itti_free (ITTI_MSG_ORIGIN_ID (received_message_p), received_message_p);
		received_message_p = NULL;
	}
}

int main()
{
	 CHECK_INIT_RETURN (itti_init (TASK_MAX, THREAD_MAX, MESSAGES_ID_MAX, tasks_info, messages_info,
#if ENABLE_ITTI_ANALYZER
				           messages_definition_xml,
#else
					             NULL,
#endif
						               NULL));

	// int itti_create_task(task_id_t task_id, void *(*function)(void *), void *args_p);
	if (itti_create_task (TASK_DEMO_RECEIVER, &demo_receiver_thread, NULL) < 0) {
    	printf("Error while creating TASK_DEMO_RECEIVER task\n");
    	return -1;
  	}
  	
	// MessageDef *itti_alloc_new_message(task_id_t origin_tid, MessagesIds msg_id);
	MessageDef *message_p = itti_alloc_new_message(TASK_DEMO_SENDER, MESSAGE_DEMO);
	if (message_p) {
		//use the macro which is defined in the demo_messages_types.h 
		DEMO_DATA_IND (message_p).name = "zgw";
		DEMO_DATA_IND (message_p).university = "SYSU";
		//int itti_send_msg_to_task(task_id_t dest_tid, instance_t inst, MessageDef *mesg);
		int send_res = itti_send_msg_to_task(TASK_DEMO_RECEIVER, INSTANCE_DEFAULT, message_p);
	}
	sleep(3);
	return 0;
}
