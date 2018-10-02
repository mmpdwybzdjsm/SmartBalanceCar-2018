#include "Driver.h"
extern struct InfoStruct Info;
extern struct FilterStruct Filter;
extern struct ParameterStruct Parameter;
extern struct FlagStruct Flag;

extern int16 mpu_gyro_x,mpu_gyro_y,mpu_gyro_z;
extern int16 mpu_acc_x,mpu_acc_y,mpu_acc_z;
void SystemInit(){
  
    OLED_Init();
    OLED_P6x8Str(0,0,"No Touching !");//�������
      
    
    DisableInterrupts;
    //adc��ʼ��
    adc_init(ADC0_SE8);//C0
    adc_init(ADC0_SE9);//C1
    adc_init(ADC0_SE10);//C2
    adc_init(ADC0_SE11);//C3
    adc_init(ADC0_SE12);//F4
    adc_init(ADC0_SE13);//F5
    adc_init(ADC0_SE14);//F6
    adc_init(ADC0_SE15);//F7
    adc_init(ADC0_SE2);//A6

    //����led��ʼ��
    gpio_init(G0,GPO,0);//Led on board
    port_pull(G0);
    gpio_init(G1,GPO,0);
    port_pull(G1);
    gpio_init(G2,GPO,0);
    port_pull(G2);
    gpio_init(G3,GPO,0);
    port_pull(G3);
    
    IIC_init();
    InitMPU6050();//��ʼ��imu
    
    //���ڳ�ʼ�� ���������ж�
    uart_init(uart0,BAUD);   //��ʼ������1Ϊ1λ��ʼλ��8λ����λ��1λֹͣλ��������9600
    //uart_rx_irq_en(uart0);
    //set_irq_priority(UART0_IRQn,1);
    
    uart_init(uart2,BAUD);   //��ʼ������1Ϊ1λ��ʼλ��8λ����λ��1λֹͣλ��������9600
    // uart_rx_irq_en(uart2);
    //set_irq_priority(UART2_IRQn,1);
    //motor��ʼ��
    ftm_pwm_init(ftm2,ftm_ch2,MotorFreq,MotorDuty0);//��ʼ��PWMƵ��Ϊ15K
    ftm_pwm_init(ftm2,ftm_ch3,MotorFreq,MotorDuty0);
    ftm_pwm_init(ftm2,ftm_ch4,MotorFreq,MotorDuty0);
    ftm_pwm_init(ftm2,ftm_ch5,MotorFreq,MotorDuty0);
    //���뿪�س�ʼ��
    gpio_init(F0,GPI,0);//gpio_get Switcher
    gpio_init(F1,GPI,0);
    gpio_init(D3,GPI,0);
    gpio_init(D4,GPI,0);
   gpio_init(D5,GPI,0);
    port_pull(F0);
    port_pull(F1);
    port_pull(D3);
    port_pull(D4);
    //port_pull(D5);
    //��ɫled��ʼ��
    gpio_init(D0,GPO,0);//LED 4 color
    gpio_init(D1,GPO,0);
    gpio_init(H6,GPO,0);
    gpio_init(H7,GPO,0);
    port_pull(D0);
    port_pull(D1);
    port_pull(H6);
    port_pull(H7);
    
     gpio_init(C6,GPO,0);
     port_pull(C6);
     
     
    //EncoderInit
    ftm_count_init(ftm0);   //��E0���������������м���    E0�ӱ�����LSB    
    gpio_init(C5,GPI,0);    //�����жϷ���                  C5�ӱ�����DIR
    port_pull(C5);          //IO����
    ftm_count_init(ftm1);   //��E7���������������м���    E7�ӱ�����LSB
    gpio_init(H5,GPI,0);    //�����жϷ���                  H5�ӱ�����DIR
    port_pull(H5);          //IO����
    
    //Button
    kbi_init(KBI0_P0,IRQ_FALLING);//A0
    kbi_init(KBI0_P1,IRQ_FALLING);//A1
    kbi_init(KBI0_P2,IRQ_FALLING);//A2
    kbi_init(KBI0_P3,IRQ_FALLING);//A3
    kbi_init(KBI0_P23,IRQ_FALLING);//C7
    kbi_init(KBI0_P26,IRQ_FALLING);//D2
    kbi_init(KBI0_P29,IRQ_FALLING);//D5
    
    set_irq_priority(KBI0_IRQn,3);
    enable_irq(KBI0_IRQn);
    
    //TeleControl
    kbi_init(KBI1_P10,IRQ_RISING);//F2
    kbi_init(KBI1_P11,IRQ_RISING);//F3
    kbi_init(KBI1_P2,IRQ_RISING);//E2 
    kbi_init(KBI1_P3,IRQ_RISING);//E3    
    //kbi_init(KBI1_P4,IRQ_RISING);//E4 VT
    set_irq_priority(KBI1_IRQn,3);					//�������ȼ�,�����Լ����������� �����÷�ΧΪ 0 - 3
    enable_irq(KBI1_IRQn);
    
    uint8 i=0;
    for(i=0;i<10;i++){//��βɼ�ʹ�����ȶ�
      Get_Gyro();
      Get_AccData();
    }
    
 //   for(i=0;i<50;i++){//���������ǻ�׼����
 //     Get_Gyro();
 //     Info.gyro_y_offset+=mpu_gyro_y;
 //     Info.gyro_z_offset+=mpu_gyro_z;
//      Info.gyro_x_offset+=mpu_gyro_x;
//      systick_delay_ms(1);
//    }
    
    Info.gyro_y_offset/=50.0f;
    Info.gyro_z_offset/=50.0f;
    Info.gyro_x_offset/=50.0f;
    
    Info.gyro_x_offset=3;
    Info.gyro_y_offset=-8;
    Info.gyro_z_offset=-3;
    
    //Info.gyro_y_offset-=1;
    Get_AccData();
    Info.acc_z_offset=Acc_Z_Offset;
    Info.acc_z=Info.acc_z_offset-mpu_acc_z;
    Info.angle=Info.acc_z;//���µ�ǰ�Ƕȼ��������ٶ�
    Info.angleIntegral=Info.acc_z;
    //for(i=0;i<5;i++)Filter.angleBuff[i]=Info.acc_z;
    Info.angle_last=Info.acc_z; 
    OLED_Fill(0x00);

    //Master Timer
    pit_init_ms(pit0,1);	            //	����ʱ��
    set_irq_priority(PIT_CH0_IRQn,0);	//����pit0���ȼ�
    enable_irq(PIT_CH0_IRQn);			//����pit0�ж�
    
    EnableInterrupts;
}

void ParameterSetting(){
    Parameter.P_Balance=34;
    Parameter.D_Balance=36;//120
    Parameter.P_Speed=27;
    Parameter.I_Speed=70;//38
    Parameter.P_Turn=105;//140
    Parameter.D_Turn=23;//30
    //Parameter.ExpectSpeed=40;
    Flag.FlagMotor=-1;
    Flag.TurnEnable=1;
    Info.DirIntegral=0;
    Info.ExpectSpeed=315;
    Info.ExpectAD=3300;
}




void UpdataDuty(){
  Info.dutyL=LIMIT(Info.dutyL,-MotorDuty0,MotorDuty0);
  Info.dutyR=LIMIT(Info.dutyR,-MotorDuty0,MotorDuty0);
  if(Info.dutyL<=0){
    ftm_pwm_duty(ftm2,ftm_ch2,MotorDuty0-0);
    ftm_pwm_duty(ftm2,ftm_ch3,MotorDuty0-(uint32)(-Info.dutyL));
  }else{
    ftm_pwm_duty(ftm2,ftm_ch3,MotorDuty0-0);
    ftm_pwm_duty(ftm2,ftm_ch2,MotorDuty0-(uint32)(Info.dutyL));
  }
  if(Info.dutyR>=0){
    ftm_pwm_duty(ftm2,ftm_ch4,MotorDuty0-0);
    ftm_pwm_duty(ftm2,ftm_ch5,MotorDuty0-(uint32)(Info.dutyR));
  }else{
    ftm_pwm_duty(ftm2,ftm_ch5,MotorDuty0-0);
    ftm_pwm_duty(ftm2,ftm_ch4,MotorDuty0-(uint32)(-Info.dutyR));
  }

}