#include "gps.h"

static uint8_t fofa = 0;
const float FINAL_lng = 31.2793591, FINAL_lat = 30.0641159 ;
extern float currentLat, currentLong;
extern float oldLat, oldLong;

void GPSread()
{
    char  GPSValues[100], parseValue[12][20], *token;

    float latitude = 0.0, longitude = 0.0, sec = 0.0, result = 0.0, min = 0.0;
    int index = 0, deg;
    char c1;
    do
    {
        c1 = UART_Read();
        switch (c1)
        {
        case '$':
            fofa++;
            break;
        case 'G':
            fofa = fofa==1?2:0;
            break;
        case 'P':
            fofa = fofa==2?3:0;
            break;
        case 'R':
            fofa = fofa==3?4:0;
            break;
        case 'M':
            fofa = fofa==4?5:0;
            break;
        case 'C':
            fofa = fofa==5?6:0;
            break;
        case ',':
            if(fofa != 6) break;
            fofa=7;
            c1 =  UART_Read();
            //get values in GPMRC until *A
            while (c1 != '*') {
                GPSValues[index] = c1;
                c1 =  UART_Read();
                index++;
            }
            /*cut string GPS values put it in ParseValue*/
            index = 0;
            token = strtok(GPSValues, ",");//cut until you find ","
            //walk through other tokens 
            while (token != NULL) {
                strcpy(parseValue[index], token);//copy what is in token into parseValue
                token = strtok(NULL, ",");
                index++;
            }
            // if SaveValue[1] = "A" Active , or , "V" Void
            if (strcmp(parseValue[1], "A") == 0) 
            {
                latitude = my_atod(parseValue[2]);//convert latitude value from string to float
                longitude = my_atod(parseValue[4]);//convert longitude value from string to float
                /*caluclate latitude*/
                deg = latitude / 100;
                min = latitude - (float)(deg * 100);
                sec = min / 60.00;
                result = deg + sec;
                currentLat = result;//save the latitude reading

                /* calculate longitude*/
                deg = longitude / 100;
                min = longitude - (float)(deg * 100);
                sec = min / 60.00;
                result = deg + sec;
                currentLong = result;//save the longitude reading
            }
            else
            {
                fofa = 0;
            }

            break;
        default:
            fofa = 0;
            break;
        }
				
    } while (fofa != 7);
}


float ToRAD(float angle){
    return angle * PI / 180;
}


float dist(void){
    int R=6371000;
    float oldLatrad = ToRAD(oldLat); 
    float currentLatrad = ToRAD(currentLat);
    float longDiff = ToRAD(currentLong-oldLong);
    float latDiff = ToRAD(currentLat-oldLat);
    float a = pow(sin(latDiff/2.0), 2.0)+cos(currentLatrad)*cos(oldLatrad)*pow(sin(longDiff/2.0), 2.0);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    float yarab = R*c;
		if(yarab<20000 && yarab > 1)
			return yarab;
		else 
				return 0;
}

float Finaldist(void){
    int R=6371000;
    float currentLatrad = ToRAD(currentLat); 
    float finalLatrad = ToRAD(FINAL_lat);
    float longDiff = ToRAD(FINAL_lng-currentLong);
    float latDiff = ToRAD(FINAL_lat-currentLat);
    float a = pow(sin(latDiff/2.0), 2.0)+cos(currentLatrad)*cos(finalLatrad)*pow(sin(longDiff/2.0), 2.0);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R*c;
}

float my_atod(char *obaa){
		float val = 0;
		uint8_t i =0;
		for(i=0;i<11;i++){
			if(obaa[i]=='.')
					continue;
			else if(obaa[i]==0 || obaa[i]=='\n')
					break;
			val *= 10.0;
			val += (uint8_t)obaa[i] - 48;
		}
		val /= 100000.0;
		return val;
}
