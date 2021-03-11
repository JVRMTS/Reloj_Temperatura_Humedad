<?php
    // config.php
    // Credenciales
	// selecion de bd
    $dbhost = "localhost";
    $dbuser = "****"; //Usuario de la base de datos
    $dbpass = "****"; //Contraseña de la base de datos
    $dbname = "sensores";
    // Conexión con la base de datos
    $con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);
?>