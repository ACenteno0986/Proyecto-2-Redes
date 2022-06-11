##### Ingeniería en Computación
##### Curso: Redes
##### Yerlyn Guerrero León - 2018175922
##### Alejandro Centeno - 2017169579
##### Carnet: 2018175922  

&nbsp;  

# **Proyecto 2**

&nbsp;

## **Ejecutar proyecto**

* Primero se debe ejecutar el siguiente comando:

        docker-compose up

* Luego se debe ejecutar :

	    docker-compose up

&nbsp;

## **Pruebas realizadas:**

### **DNS interceptor**

Para conocer que el interceptor está tomando correctamente el buffer se realizaron los siguientes pasos:

* Ejecutar mediante nslookup los siguiente comandos:

        server 127.0.0.1

        www.google.com

* Ingresar al container mediante el siguiente comando:

        docker exec -it server bash

* Una vez dentro del contenedor, ejecutar lo siguiente:

        hexdump log.txt.

### **Elasticsearch**

* Para comprobar que el contenedor con elasticsearch funcionaba se corrió el siguiente comando en la terminal el cual mostraba el mensaje ***YOU KNOW, FOR SEARCH***.

        curl localhost:9200

* Para comprobar que el contenedor de Kibana funcionara correctamente la prueba realizada fue introcuciendo en el browser la siguiente dirección, en donde si salía el mensaje ***Kibana server is not ready yet*** indica que no se está conectando.

        http://localhost:5601

&nbsp;

## Recomendaciones:

1. Se recomienda que no se corran los scripts solamente por fuera de Docker ya que puede haber diferencias e incluso no servir cuando se añade a un contenedor.

2. Tener muy clara la estructura de la información que se está transportando, en este caso los headers del DNS, para poder manipularlos de forma correcta.

3. Se recomienda utilizar Ubuntu 18, tanto para la virtualización con Docker como para la creación de las imagenes, puesto que muchos de los modulos son más estables en esta versión.

4. Remover todos los programas y servicios que estén usando el puerto 53, para evitar problemas con los módulos.

5. Utilizar nslookup y postman para verificar que los componentes del programa estén escuchando.

6. No utilizar las funciones estándar de C para string cuando se está trabajando con bytes. Aunque los valores por detrás estén intactos, las representaciones dadas por C puede estar incompletas.

7. Al iniciar este proyecto se recomienda tener conocimientos básicos o investigar sobre la herramienta Docker, esto facilitará la curva de aprendizaje presente en el proyecto.

8. Se recomienda el uso de una maquina virtual para realizar las configuraciones necesarias de la red, esto para evitar desconfigurar las opciones de red del sistema en la maquina fisica.

9. Se recomienda hacer un uso adecuado de la memoria tanto de la computadora como de la maquina virtual, ya que la mala administración de estas puede afectar el rendimiento y ralentizar el proceso del proyecto.

10. Ir poco a poco creando y conectando los contenedores y probando que su funcionamiento sea el esparado.

## Conclusiones:

1. El uso de un DNS interceptor puede ser de utilidad si queremos gestionar de forma manual el flujo de las conexiones dentro de una red, y poder decidir por dirigir las solicitudes.

2. El uso de protocolos UDP hace un poco más sencilla la comunicación entre servicios, pero no garantiza que de verdad estos se encuentren comunicando. En nuestro caso, problemas con el formato de los datos enviados a través del DNS API generaba que no se obtuviera ningún tipo de respuesta del servidor.

3. Al utilizar imagenes basadas en linux, ubuntu en nuestro caso, con funcionalidades minimas, era necesario instalar las herramientas complementarias para poder utilizar ciertos comandos.

4. Evitar imprimir directamente dentro de los contenedores a la consola porque pueden ocurrir fallas como en nuestro caso es mejor escribir en un archivo los outputs en forma de log.

5. El uso de docker-compose ayuda a automatizar la ejecución de comandos y los reduce a ejecutar un par de lineas en terminal, lo cual permite estandarizar la ejecución de ciertos proyectos.

6. La creación de contenedores ayuda a simular de forma más precisa una situación más real, donde tengo diversas maquinas prestando diferentes servicios.

7. La curva de aprendizaje para el uso de docker pudo haber sido un factor importante en el desarrollo del proyecto, la creación y el manejo de lo Dockerfiles fue un proceso complicado de entender.

8. Consideramos que el uso de Docker nos complicó el desarrollo del proyecto debido a los grandes errores que nos daba con los script a pesar de que estos estuvieran bien.

9. Se debe tener cuidado con el manejo de la memoria cuando se utilizan datos binarios. Muchas veces la memoria queda sucia y eso afecta a la información almacenada..

10. La curva de aprendizaje que Docker suele ser bastante pesada por lo que si ocurre un error se suele durar bastante tiempo buscando la solución.
