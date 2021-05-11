#include "tof_task.h"

void init_tof_thread() {
    //dbgEvent(TOF_PREINIT);
    pthread_t thread;
    pthread_attr_t attrs;
    struct sched_param priParam;
    int retc;
    int detachState;

    pthread_attr_init(&attrs);

    detachState = PTHREAD_CREATE_DETACHED;
    retc = pthread_attr_setdetachstate(&attrs, detachState);
    if (retc != 0) {
        // fail
    }

    retc |= pthread_attr_setstacksize(&attrs, TOFTHREADSTACKSIZE);
    if (retc != 0) {
        //fail
    }

    priParam.sched_priority = TOFPRIORITY;
    pthread_attr_setschedparam(&attrs, &priParam);

    retc = pthread_create(&thread, &attrs, tof_task, NULL);
    if (retc != 0) {
        //dbgEvent( FATAL_CHAIN_INIT );
        // PUT A NEW DEBUG EVENT HERE SOON
    }

    //dbgEvent(TOF_THREAD_CREATED);
}

void *tof_task() {
    static UART_Handle uart;
    static UART_Params uartParams;
    static char tof_data;

    UART_init();
	uartParams.readMode = UART_MODE_BLOCKING;
	uartParams.readDataMode = UART_DATA_BINARY;
	uartParams.baudRate = 9600;
	uartParams.readEcho = UART_ECHO_OFF;
	uartParams.stopBits = UART_STOP_ONE;
	uartParams.parityType = UART_PAR_NONE;
	uartParams.dataLength = UART_LEN_8;

	uart = UART_open(CONFIG_UART_1, &uartParams);

	if (uart == NULL) {
	    // uart did not open successfully
	}

	while (1) {
	    dbgEvent(TOF_PRESENSOR_READ);
	    UART_read(uart, &tof_data, sizeof(tof_data));
	    update_tof_FSM(tof_data);
	    dbgEvent(TOF_POSTSENSOR_READ);
	    //sendControlMessage(&message_out);
	}
}
