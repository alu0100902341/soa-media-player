# Información de la práctica

## Compilación:
1. 
2. 
3. 
4. 

## Características implementadas

Se recomienda encarecidamente la utilización de la versión de QT Creator 5.8 para evitar problemas a la hora de ejecutar el programa (por ejemplo, para poder utilizar el objeto QCameraInfo). Sin la versión adecuada es altamente probable que de errores de versión.

Se ha dividido el código en varias partes para facilitar su lectura:

 1. Beginning. En esta parte encontraremos principalmente el constructor y el destructor de la clase:
  - Constructor: Inicializa los atributosy llama a las funciones necesarias para Configurar la webcam, Crear los Iconos necesarios  para los botones (mediante QIcon y QPixMap en vez de mediante la "ui"), Crear los menús desplegables de los botones Forward/Rewind y una última función para Manejo de errores
   - Destructor: Libera el espacio de memoria de los atributos que la utilizan
 
 2. Webcam Configuration. Almacenamos en nuestra lista de objetos QCameraInfo todas las cámaras disponibles en el ordenador y creamos de forma predeterminada una QCamera camera con el primero de los dispositivos. Además, creamos entradas en nuestra QComboBox por cada dispotivo de la lista. De manera adicional se implementó un menú de contexto que salta cuando hacemos click derecho sobre el botón Webcam. Dicho menú de contexto fue una prueba y su única misión es desplegar un menú con una única opción ("Configuration") que no está programada (webcamContextMenu() y configuration_action()).

 3. Icons. En esta parte declaramos todos nuestros recursos (Imágenes en este caso), creamos nuestros iconos con ellas y las colocamos en los respectivos botones. Cabe destacar play_icon() y pause_icon(). La finalidad de estas dos es sustituir el icono del botón PlayPause cuando sea necesario (al parar un vídeo, al iniciar un vídeo, al hacerle stop...). Es poco práctico pero no he conseguido que QPixmap y QIcon dejen de quejarse cuando intento utilizarlos como atributo de mi rpograma (Con los cuál me ahorraría los dos slots y podría cambiarlos con un setIcon).

 4. Forward and Rewind Pop-Up menus. En esta parte creamos las diferentes QAction que tendrán nuestros menus (velocidades), conectamos sus señales a sus respectivos slots (los cuáles utilizan una función llamada Speed(qreal que cambia el PlayBackRate por los valores reales predeterminados en el slot. Dicha muestra un menú si intentamos elegir una velocidad sin tener un vídeo reproduciendo), añadimos las acciones a los menus y colocamos los menus en sus respectivos botones.

 5. Error Management. En esta parte creamos 2 connect para las señales de error del reproductor QMediaPlayer "player" y para la webcam QCamera "camara" vinculando dichas señales de error a 2 slots que tratan respectivamente los errores.

 6. Button Slots. Por último tenemos los slots de los botones. En un resumen muy corto:
  - Stop: Para la camara o el reproductor si estan activos. Si se pulsa cuando ni hay vídeo reproduciendo salta un warning. Si se pulsa con un PlayBackRate distinto del normal (1.0) lo normalizamos
 
  - Play/Pause: Abre un QFileDialog si el reproductor está en estado Stopped o si la webcam está activa para abrir un archivo, guardar su ruta (con la que poder reproducirlo) y utilizarla para sacar el nombre del archivo de ella para colocarlo en la cabecera de la ventana. Si hay un vídeo reproduciendo o parado pues para/reanuda el vídeo en cuestión (cambiando siempre los iconos como corresponda)
  
  - Webcam: Para el reproductor si tiene algún vídeo. Si la webcam está activa la paramos. Si no la iniciamos con el dispositivo de cámara predeterminado
 
  - ComboBox: Pequeño menú desplegable que nos muestra todos los dispositivos de cámara disponibles y nos da a elegir entre ellos. La selección la utilizará para iniciar la webcam con ella
 
## Referencias utilizadas: Guías de QT, StackOverflow e internet en general.

# Media Player

Con la ayuda de Qt vamos a crear nuestro propio reproductor multimedia. Una hermano probre de VLC que podrá tanto reproducir archivos de vídeo como mostrarnos lo que ve nuestra webcam.

## Cómo empezar

 1. Acepta la [tarea asignada de GitHub Classroom](https://classroom.github.com/assignment-invitations/46f88252daeca0a45aa569491fef1c00). Así obtendrás tu propio repositorio como una copia de este. A este repositorio lo llamaremos `upstream`.
 2. Haz un [fork](https://guides.github.com/activities/forking/) de `upstream`. Al nuevo repositorio lo llamaremos `origin`.
 3. [Clona](http://gitref.org/creating/#clone) `origin` en tu ordenador.
 4. Trabaja en tu copia local para desarrollar tu reproductor multimedia, siguiendo los pasos indicados en el siguiente apartado.
 5. Modifica README.md usando [Markdown](https://guides.github.com/features/mastering-markdown/) para:
   1. Explicar cómo compilar y probar la aplicación, incluyendo los requisitos requeridos para hacerlo.
   3. Comentar las características implementadas.
 5. [Sube](http://gitref.org/remotes/#push) los cambios al repositorio `origin` en GitHub.
 6. Crea un [pull request](https://help.github.com/articles/creating-a-pull-request) de `origin` a `upstream` para entregar la práctica.

## Reproductor multimedia

Acceder a una webcam es muy sencillo con QCamera. Tiene un método setViewfinder() que permiten indicar el control que se va a usar como visor de la webcam para ver lo que captura. Dicho control debe ser un objeto de la clase QVideoWidget. En [este artículo](https://jmtorres.webs.ull.es/me/2014/02/capturando-secuencias-de-video-con-qt/) se puede ver un ejemplo usando QCameraViewfinder como control, aunque sirve cualquier QVideoWidget —QCameraViewfinder es una clase derivada de QVideoWidget—.

Por otro lado, para reproducir un archivo de vídeo se necesita un objeto QMediaPlayer, que tiene un método setVideoOutput() para indicarle el control QVideoWidget donde mostrar el vídeo. En la [página sobre QMediaPlayer](http://doc.qt.io/qt-5/qmediaplayer.html#details) de la documentación de Qt hay varios ejemplos de cómo usarlo.

Por lo tanto para hacer un reproductor multimedia necesitaremos añadir a nuestra ventana principal un control QVideoWidget, así como botones:

 * Play / Pause, para iniciar o pausar la reproducción de una película.
   * Si no se está reproduciendo nada o se está viendo la webcam, al pulsar este control se deberá abrir un cuadro de diálogo para seleccionar el archivo de vídeo y después comenzar la reproducción.
   * Si se estaba reproduciendo un archivo, esta se pondrá en pausa.
 * Webcam, para iniciar la captura de la webcam.
 * Stop, para detener la reproducción del archivo o la captura de la webcam.
 * Rewind, para reproducir la película hacia atrás. Debe estar desactivado si no se está reproduciendo una película.
 * Forward, para reproducir la película hacia adelante de forma acelerada. Debe estar desactivado si no se está reproduciendo una película.
 
QMediaPlayer tiene métodos para controlar la velocidad y el sentido de la reproducción.
 
Lamentablemente el diseñador de Qt Creator no nos pemite añadir controles QVideoWidget. En su lugar podemos añadir un control básico QWidget y usar la opción _Promote to..._ —en menú contextual con el botón derecho del ratón sobre el control— para indicar que durante la ejecución realmente queremos que sea un QVideoWidget. Más detalles en la [documentación de Qt](http://doc.qt.io/qt-4.8/designer-using-custom-widgets.html#promoting-widgets).

## Opcional

 1. Mostrar en la barra de estado de la ventana el nombre del archivo que se está reproduciendo o el nombre descriptivo de la webcam, según el modo en el que esté el programa. En el apartado _Acceder a un dispositivo específico_ del [artículo del blog](https://jmtorres.webs.ull.es/me/2014/02/capturando-secuencias-de-video-con-qt/) se ve como se obtiene el nombre descriptivo de cada dispositivo webcam detectado.
 2. Añadir un botón que abra un cuadro de diálogo para preconfigurar la webcam a utilizar. No dudes en preguntar en caso de dudas sobre cómo añadir nuevos cuadros de diálogo a tu aplicación.
