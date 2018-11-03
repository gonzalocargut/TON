# TON
Retardo al encendido

La libreria proporciona el codigo necesario para procesar un retardo al encendido, este es controlado a traves de la funcion millis()<br>
Se posee solo una funcion que realiza los calculos pertinentes utilizando una estructura tipo TIMER definida dentro del mismo archivo.<br>
Cada temporizador que se quiera usar estara dominado por una variable de tipo TIMER, esta se debera entregar como argumento a la rutina TON.<br>

La estructura TIMER consta de los siguientes elementos:<br>

	unsigned long Acumulado: 	Tiempo acumulado desde que la condicion de entrada tomo el valor 1.
	unsigned long Preset: 		Tiempo limite para dar por terminado el conteo de tiempo, activa la 
					variable  Terminado.
	unsigned long AcumuladoAnt: 	Tiempo acumulado en el escaneo anterior de la funcion TON para la 
					instancia de TIMER en particualar.
	bool Terminado: 		Salida final del timer, es 1 cuando la variable Acumulado alcanza o 
					sobrepasa la variable Preset.
	bool Temporizando: 		Salida que permanece en 1 mientras el timer este contando tiempo.
	
	*Todas las variables de tiempo estan expresadas en milisegundos
  
La funcion esta definida segun sigue:<br>

	static bool TON(bool Condicion, TIMER &_TON)
	
	bool Condicion: 	Condicion de entrada al timer, si es 1 durante el tiempo indicado en Preset el 
				valor retornado por la funcion sera uno, de lo contrario sera 0
	TIMER &_TON: 		Variable tipo TIMER que almacena los datos de configuracion y estado del timer, 
				notese que se pasa por referencia, indicando que modifica la variable que se 
				le entrega
	Valor devuelto: 	Es 1 cuando Condicion ha pasado un tiempo Preset en estado 1
  
# Modo de uso

para utilizar un timer, es necesario definir una variable de tipo TIMER con aclanze global (fuera de cualquier funcion), por ejemplo:<br>

	TIMER temporizador;
	void setup(){
		temporizador.Preset=1000; //contar un segundo
		pinMode(4,INPUT);
		pinMode(3,OUTPUT);
	}
	void loop(){
		digitalWrite(3,TON(digitalRead(4),temporizador));
	}

En ese ejemplo, la salida 3 se activara cuando la entrada 4 hubiera permanecido por lo menos 1 segundo en uno logico, apagandose cuando la entrada 4 se apague, el efecto es un retardo al encendido.<br>
si se desea que la salida permanesca activa por un segundo al pulsar el boton, se debe utilizar la variable Temporizando:<br>

	TON(digitalRead(4),temporizador); //no olvidar llamar la funcion TON antes
	digitalWrite(3,temporizador.Temporizando);
