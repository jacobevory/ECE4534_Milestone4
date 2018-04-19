
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
        PLIB_OC_PulseWidth16BitSet(OC_ID_1, (uint16_t)val*DRV_TMR0_PeriodValueGet()/100);
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, !dir);
        DRV_OC0_Start();
        return;
    }
    
    void setMotorR(bool dir, int val){
        DRV_OC1_Stop();
        if (val > 100) val = 100;
        motor.rightPower = val*DRV_TMR0_PeriodValueGet()/100;
        motor.rightDir = dir;
        PLIB_OC_PulseWidth16BitSet(OC_ID_2, (uint16_t)val*DRV_TMR0_PeriodValueGet()/100);
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, !dir);
        DRV_OC1_Start();
        return;
    }
    void Motor_Initialize(void){
        PLIB_PORTS_DirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_C,  0x4000);
        PLIB_PORTS_DirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_G,  0x0001);
        DRV_TMR0_Start();
        motor.leftSpeed = 0;
        motor.rightSpeed = 0;
        motor.leftDir = FORWARD;
        motor.rightDir = FORWARD;
        setMotorR(FORWARD, 0);
        setMotorL(FORWARD, 0);
    }

    void MOTOR_Tasks(void){
        motor.demo_int = REVERSE;
        for(;;){
            uint32_t demo_for_int;
            if(motor.demo_int == FORWARD) motor.demo_int = REVERSE;
            else if (motor.demo_int == REVERSE) motor.demo_int = FORWARD;
            for(demo_for_int = 0; demo_for_int < 100; demo_for_int+=10){
                setMotorR(motor.demo_int, demo_for_int);
                setMotorL(motor.demo_int, demo_for_int);
                vTaskDelay(1000);
            }
        }
    }
/* *****************************************************************************
 End of File
 */
