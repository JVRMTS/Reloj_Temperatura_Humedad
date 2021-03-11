<!--
Creado por JMTS
11 de marzo de 2021
-->
<?php
function consulta0(){
	include 'config.php';
    $mysqli = $con;

    /* verificar la conexión */
    if ($mysqli->connect_errno) {
    printf("Conexión fallida: %s\n", $mysqli->connect_error);
    exit();
    }

    $consultar = "SELECT * FROM datos WHERE id=(SELECT MAX(id) FROM datos WHERE ubicacion=1)";

    if ($resultado = $mysqli->query($consultar)) {

    /* obtener un array asociativo */
        while ($fila = $resultado->fetch_assoc()) {
            printf ("<li>Temperatura: %s\n ºC</li> ", $fila["temperatura"]);
            printf ("<li>Humedad: %s\n </li> ", $fila["humedad"]);
            printf ("<li>Sensaci&oacuten T&eacutermica: %s\n ºC</li>", $fila["sen_termica"]);
        }

    /* liberar el conjunto de resultados */
    $resultado->free();
    }
    
}
function consulta1(){
	include 'config.php';
	$mysqli = $con;
    /* verificar la conexión */
    if ($mysqli->connect_errno) {
        printf("Conexión fallida: %s\n", $mysqli->connect_error);
        exit();
    }

    $consulta0 = "SELECT temperatura FROM datos WHERE temperatura=(SELECT MAX(temperatura) FROM datos WHERE ubicacion=1) LIMIT 1";
	$consulta1 = "SELECT humedad FROM datos WHERE humedad=(SELECT MAX(humedad) FROM datos WHERE ubicacion=1) LIMIT 1";
    $consulta2 = "SELECT sen_termica FROM datos WHERE sen_termica=(SELECT MAX(sen_termica) FROM datos WHERE ubicacion=1) LIMIT 1";
						
	$resultado = mysqli_query($mysqli, $consulta0);
    $fila = mysqli_fetch_assoc($resultado);
    printf ("<li>Temperatura: %s\n ºC </li> ", $fila["temperatura"]);
                    
    /* liberar el conjunto de resultados */
    $resultado->free();
                    
	$resultado = mysqli_query($mysqli, $consulta1);
    $fila = mysqli_fetch_assoc($resultado);
    printf ("<li>Humedad: %s\n </li> ", $fila["humedad"]);
                    
    /* liberar el conjunto de resultados */
    $resultado->free();
                    
	$resultado = mysqli_query($mysqli, $consulta2);
    $fila = mysqli_fetch_assoc($resultado);
    printf ("<li>Sensaci&oacuten T&eacutermica: %s\n ºC </li> ", $fila["sen_termica"]);
                    
    /* liberar el conjunto de resultados */
    $resultado->free();
}
function consulta2(){
	include 'config.php';
	$mysqli = $con;
	/* verificar la conexión */
	if ($mysqli->connect_errno) {
		printf("Conexión fallida: %s\n", $mysqli->connect_error);
		exit();
	}

	$consulta0 = "SELECT temperatura FROM datos WHERE temperatura=(SELECT MIN(temperatura) FROM datos WHERE ubicacion=1) LIMIT 1";
	$consulta1 = "SELECT humedad FROM datos WHERE humedad=(SELECT MIN(humedad) FROM datos WHERE ubicacion=1) LIMIT 1";
	$consulta2 = "SELECT sen_termica FROM datos WHERE sen_termica=(SELECT MIN(sen_termica) FROM datos WHERE ubicacion=1) LIMIT 1";
	
	$resultado = mysqli_query($mysqli, $consulta0);
	$fila = mysqli_fetch_assoc($resultado);
	printf ("<li>Temperatura: %s\n ºC </li> ", $fila["temperatura"]);
	
	/* liberar el conjunto de resultados */
	$resultado->free();
	
	$resultado = mysqli_query($mysqli, $consulta1);
	$fila = mysqli_fetch_assoc($resultado);
	printf ("<li>Humedad: %s\n </li> ", $fila["humedad"]);
	
	/* liberar el conjunto de resultados */
	$resultado->free();
	
	$resultado = mysqli_query($mysqli, $consulta2);
	$fila = mysqli_fetch_assoc($resultado);
	printf ("<li>Sensaci&oacuten T&eacutermica: %s\n ºC </li> ", $fila["sen_termica"]);
	
	/* liberar el conjunto de resultados */
	$resultado->free();
}
function consulta3(){
	include 'config.php';
	$mysqli = $con;

	/* verificar la conexión */
	if ($mysqli->connect_errno) {
		printf("Conexión fallida: %s\n", $mysqli->connect_error);
		exit();
	}

	$consulta = "SELECT * FROM datos WHERE id=(SELECT MAX(id) FROM datos WHERE ubicacion=2)";

	if ($resultado = $mysqli->query($consulta)) {

		/* obtener un array asociativo */
		while ($fila = $resultado->fetch_assoc()) {
			printf ("<li>Temperatura: %s\n ºC</li> ", $fila["temperatura"]);
			printf ("<li>Humedad: %s\n </li> ", $fila["humedad"]);
			printf ("<li>Sensacion T&eacutermica: %s\n ºC</li>", $fila["sen_termica"]);
		}

		/* liberar el conjunto de resultados */
		$resultado->free();
                    }
}
function consulta4(){
	include 'config.php';
	$mysqli = $con;
	/* verificar la conexión */
	if ($mysqli->connect_errno) {
		printf("Conexión fallida: %s\n", $mysqli->connect_error);
		exit();
	}

	$consulta0 = "SELECT temperatura FROM datos WHERE temperatura=(SELECT MAX(temperatura) FROM datos WHERE ubicacion=2) LIMIT 1";
	$consulta1 = "SELECT humedad FROM datos WHERE humedad=(SELECT MAX(humedad) FROM datos WHERE ubicacion=2) LIMIT 1";
	$consulta2 = "SELECT sen_termica FROM datos WHERE sen_termica=(SELECT MAX(sen_termica) FROM datos WHERE ubicacion=2) LIMIT 1";
	$resultado = mysqli_query($mysqli, $consulta0);
	$fila = mysqli_fetch_assoc($resultado);
	printf ("<li>Temperatura: %s\n ºC </li> ", $fila["temperatura"]);
	
	/* liberar el conjunto de resultados */
	$resultado->free();
	
	$resultado = mysqli_query($mysqli, $consulta1);
	$fila = mysqli_fetch_assoc($resultado);
	printf ("<li>Humedad: %s\n </li> ", $fila["humedad"]);
	
	/* liberar el conjunto de resultados */
	$resultado->free();
	
	$resultado = mysqli_query($mysqli, $consulta2);
	$fila = mysqli_fetch_assoc($resultado);
	printf ("<li>Sensaci&oacuten T&eacutermica: %s\n ºC </li> ", $fila["sen_termica"]);
	
	/* liberar el conjunto de resultados */
	$resultado->free();
}
function consulta5(){
	include 'config.php';
	$mysqli = $con;
	/* verificar la conexión */
	if ($mysqli->connect_errno) {
		printf("Conexión fallida: %s\n", $mysqli->connect_error);
		exit();
	}

	$consulta0 = "SELECT temperatura FROM datos WHERE temperatura=(SELECT MIN(temperatura) FROM datos WHERE ubicacion=2) LIMIT 1";
	$consulta1 = "SELECT humedad FROM datos WHERE humedad=(SELECT MIN(humedad) FROM datos WHERE ubicacion=2) LIMIT 1";
	$consulta2 = "SELECT sen_termica FROM datos WHERE sen_termica=(SELECT MIN(sen_termica) FROM datos WHERE ubicacion=2) LIMIT 1";
	$resultado = mysqli_query($mysqli, $consulta0);
	$fila = mysqli_fetch_assoc($resultado);
	printf ("<li>Temperatura: %s\n ºC </li> ", $fila["temperatura"]);
	
	/* liberar el conjunto de resultados */
	$resultado->free();
	
	$resultado = mysqli_query($mysqli, $consulta1);
	$fila = mysqli_fetch_assoc($resultado);
	printf ("<li>Humedad: %s\n </li> ", $fila["humedad"]);
	
	/* liberar el conjunto de resultados */
	$resultado->free();
	
	$resultado = mysqli_query($mysqli, $consulta2);
	$fila = mysqli_fetch_assoc($resultado);
	printf ("<li>Sensaci&oacuten T&eacutermica: %s\n ºC </li> ", $fila["sen_termica"]);
	
	/* liberar el conjunto de resultados */
	$resultado->free();
	
	/* cerrar la conexión */
	$mysqli->close();
}
// consulta a la api de OPENWEATERMAP para consultar los datos del tiempo de mi localidad
function el_tiempo(){
	$html = file_get_contents('https://api.openweathermap.org/data/2.5/weather?zip=30169,es&lang=es&units=metric&appid=*****');
	$json = json_decode($html,false);
	
	$ciudad = $json->name;
	echo "<h2 class='text-center title'>".$ciudad."</h2>";
	echo '<p class="lead text-center">';			
	$icono = $json->weather[0]->icon;
	$icono1 = "<img src= http://openweathermap.org/img/wn/".$icono."@2x.png>";
	echo $icono1,"</br>";
	echo "<strong>Nubosidad: </strong>";
	$descripcion = $json->weather[0]->description;
	echo $descripcion, "</br>";

	$temp = $json->main->temp;
	echo "<strong>Temperatura actual: </strong>", $temp, " ºC</br>";
	$sen_termica = $json->main->feels_like;
	echo "<strong>Sensaci&oacuten T&eacutermica: </strong>",$sen_termica , " ºC</br>";
	$humedad = $json->main->humidity;
	echo "<strong>Humedad: </strong>",$humedad, " %</br>";
	$vel_viento = $json->wind->speed;
	echo "<strong>Velocidad del viento: </strong>",$vel_viento, " m/s</br>";
	echo "</p>";
}
?>