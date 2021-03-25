<?php
    // config.php
    // Credenciales
    // selecion de bd
    // 25/03/2021
    // @JMTS - www.jmts.es
function conectar(){
    $dbhost = "localhost";
    $dbuser = "****"; // Pon el usuario de tu base de datos
    $dbpass = "****"; // Pon la contraseña de tu base de datos
    $dbname = "****"; // Pon el nombre de tu base de datos
    // Conexión con la base de datos
    $con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);
    return $con;
}
?>