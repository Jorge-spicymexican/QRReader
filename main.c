/*
lab_6.c
Jorge Jesus Jurado-Garcia

Hardware required:
 *Launchpad with LM34

Modified 01/27/2020 by Jorge Jurado to use MSP432 Register operations
Modified 01/27/2020 by Jorge Jurado to run in Code composer studio
 */

/*  Last Lab due
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "msp432.h"
#include "ee1910delay.h"
#include "stdio.h"
#include "ee1910analog.h"
#include "ee1910millis.h"
#include "math.h"
#include "ee1910music.h"
/////////////////////////////////////////////////////////////////////////////////////////
void take_reading(int array[], int middle);
void print_reading(int b[]);
int binary2decimal(int c[]);
void intem_decoder(int burro);
void digit_display(int n);
/////////////////////////Prototypes//////////////////////////////////////////////////////
void main(void){
    int white;
    int black;
    int donkey[5];
    P1->DIR &= ~0x12;
    P1->REN |= 0x12;
    P1->OUT |= 0x12;

    analogSetup();
    printf("Please Lay over the white piece of paper over the sensor and when ready press the P1_4 button \n");
    while( (P1->IN & 0x10) != 0){ }
    while ( (P1->IN & 0x10) ==0 ){
        white = analogRead();
        printf("%d\n", white);
        break;
    }

    delay(1000);

    printf("Please Lay over the black piece of paper over the sensor and when ready press the P1_1 button\n");
    while( (P1->IN & 0x02) !=0) {}
    while ( (P1->IN & 0x02) ==0 ){
        black = analogRead();
        printf("%d\n", black);
        break;
    }

    delay(1000);

    int middle = (white+black)*0.5;
    printf("Middle value:%d\n", middle);
    delay(500);

    while(1){
        printf("Press P1_4 button to take readings\n");
        while( (P1->IN & 0x10) !=0){}
        if( (P1->IN & 0x10)==0){
            delay(1000);
            take_reading(donkey, middle);
            print_reading(donkey);
            int intem_code = binary2decimal(donkey);
            intem_decoder(intem_code);
        }
        printf("You will have 3 seconds before checking out the next item\n");
        delay(3000);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
void take_reading(int array[], int middle){
    int n=5; ////// int n= 5;
    int k=1;
    analogSetup();
    for(k=1; k<=n; k++){
        printf("%d\n", k);
        delay(1000);
        int readings = analogRead();
        if( readings < middle){
            // save o in the array for n-1
            array[k] = 0;

        }
        else{
            array[k] = 1;
            //save 1 in the array for n-1 index
        }

        digit_display(k);

    }

    delay(1000);

}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
void print_reading(int b[]){
    static int n=0;
    for(n=1; n<=5; n++){
        printf("%d\n", b[n]);   /////maybe change its label ask dr.ross
    }
    ///print out It should print out the contents of the array on
    //the console on one line.  Then it should advance to the next line.
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
int binary2decimal(int c[]){
    int intem;
    intem = 1*c[0] + 2*c[1] + 4*c[2] + 8*c[3] + 16*c[4];
    printf("Item number:%d\n",intem);
    return intem;

}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void intem_decoder(int burro){
    switch(burro){
    case 10:
        printf("Jam\n");
        make_music(440);
        delay(500);
        stop_music();
        break;

    case 13:
        printf("Milk\n");
        make_music(440);
        delay(500);
        stop_music();
        break;

    case 19:
        printf("Bread\n");
        make_music(440);
        delay(500);
        stop_music();
        break;

    case 20:
        printf("Apple\n");
        make_music(440);
        delay(500);
        stop_music();
        break;

    }
    if( burro != (10 || 13 || 19 || 20) ) {
        printf("ERROR\n");
        make_music(220);
        delay(500);
        stop_music();
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void digit_display(int a){
    P9->DIR |= 0xFF;
    P9->OUT &= ~0xFF;
    int LEDarray[] = {0x01,0x4F,0x12,0x06,0x4C,0x24,0x20,0x0F,0x00,0x04};
    switch(a){
    case 0:
        P9->OUT |= LEDarray[0];
        delay(1000);
        P9->OUT &= ~(LEDarray[0]);
        break;

    case 1:
        P9->OUT |= LEDarray[1];
        delay(1000);
        P9->OUT &= ~(LEDarray[1]);
        break;

    case 2:
        P9->OUT |= LEDarray[2];
        delay(1000);
        P9->OUT &= ~(LEDarray[2]);
        break;

    case 3:
        P9->OUT |= LEDarray[3];
        delay(1000);
        P9->OUT &= ~(LEDarray[3]);
        break;

    case 4:
        P9->OUT |= LEDarray[4];
        delay(1000);
        P9->OUT &= ~(LEDarray[4]);
        break;

    case 5:
        P9->OUT |= LEDarray[5];
        delay(1000);
        P9->OUT &= ~(LEDarray[5]);
        break;

    case 6:
        P9->OUT |= LEDarray[6];
        delay(1000);
        P9->OUT &= ~(LEDarray[6]);
        break;

    case 7:
        P9->OUT |= LEDarray[7];
        delay(1000);
        P9->OUT &= ~(LEDarray[7]);
        break;

    case 8:
        P9->OUT |= LEDarray[8];
        delay(1000);
        P9->OUT &= ~(LEDarray[8]);
        break;
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
