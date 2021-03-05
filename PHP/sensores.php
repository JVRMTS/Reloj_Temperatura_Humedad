<!--
Creado por JMTS
19 febrero 2021
-->
<!DOCTYPE html>
<html lang="es">
    <head>
        <meta charset="utf-8"/>
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
        <meta http-equiv="refresh" content="60" />
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" 
        integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
        <title>Sensores</title>
        <?php include("config.php"); ?>
    </head>
    <body>
        <header>
            <h1>SENSORES</h1>
           <!-- <nav><menu>aqui ha de ir el men&uacute;</menu></nav> -->
        </header>
        <section>
            <article>
                <h2>Sensor Despacho</h2>
                <!--Aquí va el codigo php para mostrar el sensor del despacho-->
                
                <h4>Temperatura actual</h4>
                <ul>
                <?php
                    $mysqli = $con;
                    /* verificar la conexión */
                    if ($mysqli->connect_errno) {
                        printf("Conexión fallida: %s\n", $mysqli->connect_error);
                        exit();
                    }

                    $consulta = "SELECT * FROM datos WHERE id=(SELECT MAX(id) FROM datos WHERE ubicacion=1)";

                    if ($resultado = $mysqli->query($consulta)) {

                        /* obtener un array asociativo */
                        while ($fila = $resultado->fetch_assoc()) {
                            printf ("<li>Temperatura: %s\n ºC </li> ", $fila["temperatura"]);
                            printf ("<li>Humedad: %s\n </li> ", $fila["humedad"]);
                            printf ("<li>Sensaci&oacuten Termica: %s\n ºC </li>", $fila["sen_termica"]);
                        }

                        /* liberar el conjunto de resultados */
                        $resultado->free();
                    }

                    /* cerrar la conexión */
                    //$mysqli->close();
                ?>
                </ul>
				<h4>M&aacuteximas</h4>
                <ul>
                <?php
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
                    printf ("<li>Sensaci&oacuten Termica: %s\n ºC </li> ", $fila["sen_termica"]);
                    
                    /* liberar el conjunto de resultados */
                    $resultado->free();
                    
                ?>
                </ul>
				<h4>M&iacutenimas</h4>
                <ul>
                <?php
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
                    printf ("<li>Sensaci&oacuten Termica: %s\n ºC </li> ", $fila["sen_termica"]);
                    
                    /* liberar el conjunto de resultados */
                    $resultado->free();
                ?>
                </ul>
            </article>
            <article>
                <h2>Sensor Sal&oacute;n</h2>
                <!--Aquí va el codigo php para mostrar el sensor del salón-->
                <h4>Temperatura actual</h4>
                <ul >
                <?php
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
                            printf ("<li>Sensacion Termica: %s\n ºC</li>", $fila["sen_termica"]);
                        }

                        /* liberar el conjunto de resultados */
                        $resultado->free();
                    }
                    /* cerrar la conexión */
                    //$mysqli->close();
                ?>
                </ul>
				<h4>M&aacuteximas</h4>
                <ul>
                <?php
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
                    printf ("<li>Sensaci&oacuten Termica: %s\n ºC </li> ", $fila["sen_termica"]);
                    
                    /* liberar el conjunto de resultados */
                    $resultado->free();
                ?>
                </ul>
				<h4>M&iacutenimas</h4>
                <ul>
                <?php
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
                    printf ("<li>Sensaci&oacuten Termica: %s\n ºC </li> ", $fila["sen_termica"]);
                    
                    /* liberar el conjunto de resultados */
                    $resultado->free();
                    
                    /* cerrar la conexión */
                    $mysqli->close();
                ?>
                </ul>
            </article>
        </section>
        <footer>
            <?php echo '<P>Creado por JMTS</P>';?>
        </footer>
    </body>

</html>