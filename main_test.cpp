#include <iostream>
#include <stdio.h>

#include "exceptions.h"
#include "comms.h"
#include "usbcomm.h"
#include "bluecomm.h"
#include "message.h"
#include "opcodes.h"

using namespace std;

void playTune(Comms &nxt){
    unsigned short int C=523;
    unsigned short int D=587;
    unsigned short int E=659;
    unsigned short int G=784;

    unsigned short int freq=500;
    Opcodes op(&nxt);
    op.playTone(E,freq);
    op.playTone(D,freq);
    op.playTone(C,freq);
    op.playTone(D,freq);
    op.playTone(E,freq);
    op.playTone(E,freq);
    op.playTone(E,freq);
    op.playTone(D,freq);
    op.playTone(D,freq);
    op.playTone(D,freq);
    usleep(500000);
    op.playTone(E,freq);
    op.playTone(G,freq);
    op.playTone(G,freq);
    usleep(500000);
    op.playTone(E,freq);
    op.playTone(D,freq);
    op.playTone(C,freq);
    op.playTone(D,freq);
    op.playTone(E,freq);
    op.playTone(E,freq);
    op.playTone(E,freq);
    op.playTone(E,freq);
    op.playTone(D,freq);
    op.playTone(D,freq);
    op.playTone(E,freq);
    op.playTone(D,freq);
    op.playTone(C,freq);
    sleep(1);

}

void printBatteryLevel(Comms &nxt){
    Opcodes op(&nxt);
    printf("Battery level: %hu [mv]\n",op.getBatteryLevel());
}

int main(int argc, char *argv[])
{

    //USBComm nxt;
    BlueComm nxt;
    try{
           //nxt.connect("00:16:53:13:05:B2");
           nxt.connect("00:16:53:17:B7:44");
           //Use nxt.find when on USB
           //nxt.find();
    }catch(NxtEx &ex){
        cout<<ex.toString()<<endl;
        return -1;
    }

    try{
        //playTune(nxt);
        printBatteryLevel(nxt);
        Opcodes op(&nxt);
        unsigned char status;
        MotorState ms;
        int alti = 0;
        int az = 0;
       //for (int i=1; i<10; i++){
           //az 
           //printf ("azimuth:\n");
           //ms  = op.getOutputState(0x00);
           //cout<<"az: "<<int(ms.port)<<" "<<int(ms.power)<<" "<<int(ms.mode)<<" "<<int(ms.regMode)<<" "<<int(ms.turnRatio)<<" "<<int(ms.runState)<<" "<<ms.tachoLimit<<" "<<ms.tachoCount<<" "<<ms.blockTachoCount<<" "<<ms.rotationCount<<endl;
           //SEBA: Working msg for az
           //op.setOutputState(0x00,80,0x01,0x00,50,0x20,(4.667*i),true,&status);
           op.setOutputState(0x00,80,0x01,0x00,0,0x20,(4.667*az),true,&status);
           ms = op.getOutputState(0x00);
           cout<<"port: "<<int(ms.port)<<" power: "<<int(ms.power)<<" mode:"<<int(ms.mode)<<" regMode: "<<int(ms.regMode)<<" turnRatio: "<<int(ms.turnRatio)<<" runState: "<<int(ms.runState)<<" tachoLimit: "<<ms.tachoLimit<<" tachoCount: "<<ms.tachoCount<<" blockTachoCount: "<<ms.blockTachoCount<<" rotationCount: "<<ms.rotationCount<<endl;

           //el
           printf(" angulo %d \n",alti);
           op.setOutputState(0x01,-80,0x01,0x00,50,0x20,alti/5,true,&status);//con este muevo el motor conectado a B
           op.setOutputState(0x02,80,0x01,0x00,50,0x20,alti/5,true,&status);//con este muevo el motor conectado a C
           ms = op.getOutputState(0x01);
           cout<<"port: "<<int(ms.port)<<" power: "<<int(ms.power)<<" mode:"<<int(ms.mode)<<" regMode: "<<int(ms.regMode)<<" turnRatio: "<<int(ms.turnRatio)<<" runState: "<<int(ms.runState)<<" tachoLimit: "<<ms.tachoLimit<<" tachoCount: "<<ms.tachoCount<<" blockTachoCount: "<<ms.blockTachoCount<<" rotationCount: "<<ms.rotationCount<<endl;
           ms = op.getOutputState(0x02);
           cout<<"port: "<<int(ms.port)<<" power: "<<int(ms.power)<<" mode:"<<int(ms.mode)<<" regMode: "<<int(ms.regMode)<<" turnRatio: "<<int(ms.turnRatio)<<" runState: "<<int(ms.runState)<<" tachoLimit: "<<ms.tachoLimit<<" tachoCount: "<<ms.tachoCount<<" blockTachoCount: "<<ms.blockTachoCount<<" rotationCount: "<<ms.rotationCount<<endl;
        //}
        /*op.setInputMode(0x00, LIGHT_ACTIVE, RAWMODE);
        SensorState ss;
        cout<<"Status: "<<(int)status<<endl;
        sleep(1);
        for(int i=0;i<10;i++){
            sleep(1);
            ms = op.getOutputState(0);
            cout<<"a: "<<int(ms.port)<<" "<<int(ms.power)<<" "<<int(ms.mode)<<" "<<int(ms.regMode)<<" "<<int(ms.turnRatio)<<" "<<int(ms.runState)<<" "<<ms.tachoLimit<<" "<<ms.tachoCount<<" "<<ms.blockTachoCount<<" "<<ms.rotationCount<<endl;
            op.resetMotorPosition(0,false);
            //ss = op.getInputValues(0x00); 
            //cout<<"a: "<<int(ss.port)<<" "<<ss.valid<<" "<<ss.calibrated<<" "<<ss.type<<" "<<ss.mode<<" "<<ss.rawValue<<" "<<ss.normalizedValue<<" "<<ss.scaledValue<<" "<<ss.calibratedValue<<endl;
        }*/
        //shuts down the motor
        //op.setOutputState(0x00,0,0x00,0x00,0,0x00,0,true,&status);
        //op.setOutputState(0x01,0,0x00,0x00,0,0x00,0,true,&status);
        //op.setOutputState(0x02,0,0x00,0x00,0,0x00,0,true,&status);
        nxt.disconnect();

    }catch(NxtEx &ex){
        cout<<ex.toString()<<endl;
        nxt.disconnect();
        return -1;

    }
    return 0;
}
