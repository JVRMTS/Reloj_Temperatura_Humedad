
<?php
    // 25/03/2021
    // @JMTS - www.jmts.es
    // insertar_post.php
	
    // Importamos la configuración
    require ("config.php");
	//date_default_timezone_set("Europe/Madrid");
    
	// Leemos los valores que nos llegan por POST
    $temperatura = $_POST['t'];
	$humedad = $_POST['h'];
	$sen_termica = $_POST['st'];
	$ubicacion = $_POST['ub'];
	$con = conectar();
	
	
    // Esta es la consulta para insertar los valores
    $query = "INSERT INTO datos(temperatura,humedad,sen_termica,ubicacion)VALUES($temperatura,$humedad,$sen_termica,$ubicacion)";
    
	// Ejecutamos la consulta
    mysqli_query($con, $query);
    mysqli_close($con);
	echo "Datos Ingresados Correctamente";
?>