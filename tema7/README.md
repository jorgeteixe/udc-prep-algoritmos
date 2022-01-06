# Tema 7: Compejidad computacional

La complejidad computacional es el estudio del problema, independientemente del *algoritmo* que usemos para resolverlo (incluidos algoritmos que no conocemos).

## P y NP

Se considera que un problema estratable si se puede resolver en un tiempo polinómico O(n^k) para algún k. El conjunto de estos problemas se llama clase de complejidad **P**.

En cambio hay problemas para los que no conocemos ningún algoritmo polinómico (ojo, no lo conocemos, pero podría existir). Este tipo de problemas se considera de clase de complejidad **NP** (*non-deterministic polynomial time*).

Informalmente, NP, es el conjunto de problemas cuya solución se puede comprobar en tiempo polinómico, pero no resolver. Si hubiese un ser omnipotente, y nos dijese la solución, podríamos comprobarla fácilmente. En cambio encontrarla es *otra historia*.

La **pregunta del millón** es si todos estos problemas están también en P o no, es decir, si P = NP o no.

Se cree que P ≠ NP, pero no se ha demostrado. Si esto fuese cierto, nunca encontraríamos soluciones polinómicas a problemas NP, porque sabremos que no existen.

## Máquinas de Turing

Una máquina de Turing es una máquina que manipula símbolos en una cinta según una tabla de reglas. Dado un estado, se va al siguiente.

- Una máquina de Turing **determinista**, dada una situación, se sigue un camino.
- Una máquina **no determinista**, dada una situación, puede tomar varios caminos.

La definición original de P y NP es:

- Clase de complejidad **P**: Conjunto de lenguajes (problemas booleanos, si y no) que se pueden resolver con una máquina de Turing que termina su ejecución en un número de pasos acotado por una función polinómica, O(n^k).
- Clase de complejidad **NP**: Conjunto de lenguajes (o sea, problemas si/no) que se pueden resolver con una máquina de Turing **no determinista** en un número de pasos acotado por una función polinómica, O(n^k).

Todo lo que se puede hacer en una máquina de Turing determinista se puede hacer en una máquina de Turing no determinista, y viceversa. Es fácil de entender en el sentido determinista-no determinista, simplemente, aunque tenga la capacidad de tomar varios caminos, solo toma uno. En cambio al revés, también se puede hacer... simplemente que no sería eficiente. La máquina de Turing determinista tendría que probar cada uno de los caminos secuencialmente, cambiando el orden de pasos de polinómico a exponencial.

Una máquina de Turing no determinista no existe en la realidad, no podemos probar infinitos caminos a la vez, lo análogo sería que cada vez que hay varios caminos, tomamos todos a la vez, se clona el ordenador y cada uno sigue un camino.

## NP-completitud

Existe un subconjunto de problemas NP, llamados problemas NP-completos, que tienen la siguiente propiedad:

> Si cualquiera de ellos está en P, entonces todos los problemas de NP están en P. Es decir, bastaría con encontrar un único algoritmo polinómico que resuelva un problema NP-completo para demostrar que P = NP.

De la propiedad anterior deducimos que si P ≠ NP, entonces ninguno de estos problemas puede estar en P.

Decimos que un problema es NP-completo si está en NP y cualquier problema NP es reducible a él. Un problema A es reducible en tiempo polinómico a B si, dado un algoritmo que resuelve B, podemos obtener un algoritmo que resuelve A añadiendo, como mucho, un factor polinómico a su complejidad. Si un problema *x* NP-completo está en P, todos los problemas NP podrían ser reducidos a *x* y por tanto estar en P.

Ejemplos de problemas NP completos:

- Suma de subconjuntos.
- Problema del viajante.
- Determinar si los paises de un mapa se pueden colorear con k colores sin que países adyacentes tengan el mismo color.
- Dada una lista de personas y sus enemistades, invitar al máximo de personas sin que nadie se lleve mal.
- Satisfacibilidad booleana: determinar si una expresión de lógica proposicional es verdadera para alguna combinación de valores.
- Resolver un sudoku.

Tras años intentando encontrar soluciones a problemas NP-completos sin éxito es la razón por la que muchos investigadores piensan que P ≠ NP.

Otro argumento más filosófico: "*Si P fuera igual a NP, el mundo sería diferente a lo que suponemos. Los saltos creativos no tendrían valor, no habría diferencia entre encontrar una solución y reconocerla. Cualquiera que pudiese apreciar una sinfonía sería Mozart o entender una demostración paso a paso sería Gauss...*".
