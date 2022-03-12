# <center> Proyecto C.I.</center>

### <center> FitCat </center> <br><br>

## **Objetivo**
---
Entrenar, habituar y orientar al gato a formar habitos alimenticios correctos y fomentar la actividad física. Así evitandose enfermedades y afecciones relacionadas con el sobrepeso.<br><br>

## **Qué es** 
---
**Sistema entrenador** automatico de hábitos alimentacios y **promotor de actividad física** para la prevención del sobrepeso en gatos.

Clicker automático aunado a un comedor y a un laser. <br><br>

## **Qué hace**
---

<div><img align="right" width="400" heigh="400" src="images\catFit2.png"/>&nbsp 

**Maneja y lleva un control** de la alimentación como la actividad física del gato. **Se asegura** de que no se alimente más y se hidrate lo suficiente; y **hace** que la mascota se ejercite y juegue, **gracias al estímulo de recompensa** por el tiempo recomendado.      
Así cumple con su función de inculcar y cultivar hábitos en la mascota.<br><br>

**El "clicker" se activa todos los días a las mismas horas** y lo invita a comer y **si se excede, no lo deja comer más**.<br><br>

## **CatFit consta de tres partes principales:**
---

<div><img height="400" align="right" width="400" heigh="400" src="images\catFit1.png"/>&nbsp 

* **Clicker.**  
Emite un sonido con un speaker y cuando responde al estímulo, proporciona un premio. Esto para recordarle tomar agua, comer y realizar su actividad física. Se activa también si el gato no ha cumplido con su dosis.
Entrenador "ruido-recompensa". 
Además, bajo él está el contenedor de catnip que dispensa los premios y caen por una rampa hecha con material rascador. <br><br>

* **Comedor.**  
Tienen una célula de carga con función de bascula para calcular los alimentos que ha ingerido.

    * ***Contenedor de comida.***   
    Tiene una bisagra que cierra cuando el gato ha comido >= de porción de sus alimentos establecida.

    * ***Recipiente de agua.*** Siempre está activo. <br><br>

* **Puntero.**  
Promueve el ejercicio con el láser y se mueve de forma automática junto con el sensor de movimiento.  
Cuenta con dos servomotores que hacen que ambos se muevan.  
Si cumple con el tiempo de ejercicio, se premia; y se detecta que el gato deja de jugar, pero realizó por lo menos la mitad de tiempo, se le recompensa con catnip pero en menor cantidad.<br><br></div>

<!-- <img align="left" width="400" heigh="400" src="images\catFit1.png"/> -->


<br><br>

## **Cantidades de alimento**
---

<div><img align="right" width="400" heigh="400" src="images\catFit3.jpg"/>&nbsp

| Peso  | Comida |
| ----- | ------ |
| 2kg   | 30-40g |
| 3kg   | 40-55g |
| 4kg   | 45-65g |
| 5kg   | 55-75g |
| +6kg  | 11g*kg|

<br><br>

## 🍽️ **Pasos para la alimentación**

---

1. Hacer sonar el clicker del CatFit para llamar al gato
3. Que el CatFit contabilice la cantidad de alimento ingerido (algo así como el principio de arquimedes)
4. Una vez se ingiera la cantidad establecida, cerrar la compuerta de la comida
5. Dar catnip
6. Inicializar temporizador, una vez terminado, volver al paso 1.

<br>

## 🏋️ **Pasos para la ejercitación**

---

1. Hacer sonar el clicker del CatFit
2. Activar el laser 10 minutos
3. Pasando 5 minutos, si el gato dejó de jugar, dar una pequeña ración de catnip
4. Al terminar, dar dosis completa de catip
6. Inicializar temporizador, una vez terminado, volver al paso 1.

<br>

## 🔍 **Observaciones / recomendaciones**

---

* Quitar el bebedero como parte del microcontrolador, pues no tiene tiene ninguna funcionalidad respecto al arduino.
* Evitar el tapete.
* Poner tres diferentes sonidos en el speaker para llamar al gato a hacer las tres diferentes acciones.
* Repartir tiempo de ejercitación entre más invervalos. Intercalarlo con los horarios de comida.
<br>

❓ **Preguntas**

---

- [ ] ¿esos 30 minutos de ejercicio diario se reparten al día en intervalos de 10 minutos?
- [ ] ¿el clicker se activa antes o después de que coma? si es después, ¿cómo se le llama al gato para que vaya a comer/ejercitarse?
- [x] cómo detectará el microchip si el gato está ejercitandose?
- [x] ¿también se puede exceder de agua?
- [ ] ¿por qué el laser se activa después de la segunda comida?
- [ ] ¿se activa el modo ejercitación y alimentación al mismo tiempo o se intercala?
- [ ] ¿para la alimentación sólo se activa el clicker cuando el gato no ingiere su porción completa de comida?
- [ ] ¿cuántas veces al día comerá el gato?, ¿se abrirá la compuerta en horarios establecidos? después de que suene el clicker.
- [ ] ¿se guarda la cantidad de alimentos ingeridos al día en alguna base de datos?

