#ifndef _TON_
#define _TON_
#include <stdint.h>

//*******************************************
//          Estructura Temporizador         *
//*******************************************
#ifndef _TIMER_
#define _TIMER_
struct TIMER{
  unsigned long Acumulado;
  unsigned long Preset;
  unsigned long AcumuladoAnt;
  union {
  		struct {
  			bool Terminado:1;
  			bool Temporizando:1;
  		};
  		byte Control;
  	};
};
#endif

//*******************************************
//           Retardo al Encendido           *
//*******************************************
static bool TON(bool Condicion, TIMER &_TON){
  unsigned long Muestra = millis();
  if(_TON.Terminado==1){
    if(Condicion==1){
      _TON.Terminado=1; _TON.Temporizando=0;_TON.AcumuladoAnt=Muestra; 
    }
    else{
      _TON.Terminado=0; _TON.Acumulado=0; _TON.Temporizando=0;
    }
  }
  else {
    if(Condicion==1){
      if(_TON.Acumulado>=_TON.Preset){
        _TON.Terminado=1; _TON.Temporizando=0; _TON.AcumuladoAnt=Muestra;
      }
      else{
        _TON.Acumulado=_TON.Acumulado + (Muestra-_TON.AcumuladoAnt);
        _TON.AcumuladoAnt=Muestra;
        _TON.Temporizando=1;
      }
    }
    else{
      _TON.Terminado=0; _TON.Acumulado=0; _TON.Temporizando=0;_TON.AcumuladoAnt=Muestra;
    }
  }
  return(_TON.Terminado);
}

//*******************************************
//          Reiniciar Temporizador          *
//*******************************************
#ifndef _REST_TEMPR_
#define _REST_TEMPR_
static void REST_TEMPR(TIMER &_TIMER){
  _TIMER.Terminado=0;
  _TIMER.Acumulado=0;
}
#endif

#endif
