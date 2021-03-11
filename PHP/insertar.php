<?php
    // iot.php
    // Importamos la configuración
    require("config.php");
    // Leemos los valores que nos llegan por GET
    $temperatura=$_GET['t'];
	$humedad=$_GET['h'];
	$sen_termica=$_GET['st'];
	$ubicacion=$_GET['ub'];
	
	// Esta es la instrucción para insertar los valores
    $query = "INSERT INTO datos(temperatura,humedad,sen_termica,ubicacion)VALUES($temperatura,$humedad,$sen_termica,$ubicacion)";
    // Ejecutamos la instrucción
    mysqli_query($con, $query);
    mysqli_close($con);
?>