
#include "motor_thread.h"

 
    void setDirection(bool dir){
        motor.leftDir = dir;
        motor.rightDir = dir;
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, !dir);
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, !dir);
        return;
    }
    void setDirectionL(bool dir){
        motor.leftDir = dir;
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, !dir);
        return;
    }
    void setDirectionR(bool dir){
        motor.rightDir = dir;
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, !dir);
        return;
    }
    
    void setPulseWidth(int val){
            DRV_OC0_Stop();    
            DRV_OC1_Stop();
            motor.rightPower = val;
            motor.leftPower = val;
            PLIB_OC_PulseWidth16BitSet(OC_ID_1, val);
            PLIB_OC_PulseWidth16BitSet(OC_ID_2, val);
            DRV_OC0_Start();
            DRV_OC1_Start();
    }

    void setPulseWidthL(int val){
        DRV_OC0_Stop();
        motor.leftPower = val;
        PLIB_OC_PulseWidth16BitSet(OC_ID_1, val);
        DRV_OC0_Start();
        return;
    }
    void setPulseWidthR(int val){
        DRV_OC1_Stop();
        motor.rightPower = val;
        PLIB_OC_PulseWidth16BitSet(OC_ID_2, val);
        DRV_OC1_Start();
        return;
    }
    
    void setMotorL(bool dir, int val){
        DRV_OC0_Stop();
        if (val > 100) val = 100;
        motor.leftPower = val*DRV_TMR0_PeriodValueGet()/100;
        motor.leftDir = dir;
        PLIB_OC_PulseWidth16BitSet(OC_ID_1, val*DRV_TMR0_PeriodValueGet()/100);
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, !dir);
        DRV_OC0_Start();
        return;
    }
    
    void setMotorR(bool dir, int val){
        DRV_OC1_Stop();
        if (val > 100) val = 100;
        motor.rightPower = val*DRV_TMR0_PeriodValueGet()/100;
        motor.rightDir = dir;
        PLIB_OC_PulseWidth16BitSet(OC_ID_2, val*DRV_TMR0_PeriodValueGet()/100);
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, !dir);
        DRV_OC1_Start();
        return;
    }
    void Motor_Initialize(void){
        DRV_TMR0_Start();
        motor.leftSpeed = 0;
        motor.rightSpeed = 0;
        motor.leftDir = FORWARD;
        motor.rightDir = FORWARD;
        setMotorR(FORWARD, 0);
        setMotorL(FORWARD, 0);
    }

    void MOTOR_Tasks(void){
        
        //struct encoder_message *ENCODER_MESSAGE;
        for(;;){            
            /*
            if(uxQueueMessagesWaiting( encoder.eQueue ) > 0){
                ENCODER_MESSAGE = encoder_sensor_receive();
                encoder.rightVal = ENCODER_MESSAGE->right;
                encoder.leftVal = ENCODER_MESSAGE->left;
            }
            
            dbgOutputVal((uint32_t)(encoder.rightVal*100));
            dbgOutputLoc((uint32_t)(encoder.leftVal*100));
            if(motor.TIME_TO_SEND){
                motor_send(motor.leftDir, motor.rightDir, motor.leftPower, motor.rightPower);
                motor.TIME_TO_SEND = false;
            }
           */
       
        }
    }
/* *****************************************************************************
 End of File
 */
