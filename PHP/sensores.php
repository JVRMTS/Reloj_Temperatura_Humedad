<!--
Creado por JMTS
11 de marzo de 2021
-->
<!DOCTYPE html>
<html lang="es">
    <head>
        <meta charset="utf-8"/>
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
		<meta name="description" content="Sensores de temperatura y humedad controlados por ESP32">
		<meta name="author"      content="Javier Mateos (http://www.jmts.es">
        <meta http-equiv="refresh" content="60" />
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" 
        integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
        <title>Temperaturas</title>
        <?php 
			include("consultas.php");
		?>
		
    </head>
    <body>
        <header>
            <h1 align="center">Temperaturas</h1>
           <!-- <nav><menu>aqui ha de ir el men&uacute;</menu></nav> -->
        </header>
        <section>
			<article>
			<?php
			echo el_tiempo();
			?>
			</article>
            <article>
			<div class="container" h-100>      
				<div class="row justify-content-center">
				<div class="row">
					<div class="col-md-6">
						<h2 align="center">Despacho</h2>
						<!--Aquí va el codigo php para mostrar el sensor del despacho-->
						<strong>
						<h4 align="center">Temperatura actual</h4>
						<ul class="list-unstyled" align="center">
						<li>
						<?php
							echo consulta0();
						?>
						</li>
						</strong>
						<h4 align="center">M&aacuteximas</h4>
						<li>
						<?php
							echo consulta1();
						?>
						</li>
						<h4 align="center">M&iacutenimas</h4>
						<li>
						<?php
							echo consulta2();
						?>
						</li>
						</ul>
					</div>
            		<div class="col-md-6" >
						<h2 align="center">Sal&oacute;n</h2>
						<!--Aquí va el codigo php para mostrar el sensor del salón-->
						<strong>
						<h4 align="center">Temperatura actual</h4>
						<ul class="list-unstyled" align="center">
						<li>
						<?php
							echo consulta3();
						?>	
						</li>
						</strong>
						<h4 align="center">M&aacuteximas</h4>
						<li>
						<?php
							echo consulta4();
						?>
						</li>
						<h4 align="center">M&iacutenimas</h4>
						<li>
						<?php
							echo consulta5();
						?>
						</li>
						</ul>
					</div>
				</div>
			</div>
			</div>
            </article>
        </section>
        <footer>
            <p align="center">
				CREADO POR: </BR>
				<a href="http://www.jmts.es"target="_blank">@JMTS</a> | 
				<a href="https://github.com/JVRMTS?tab=repositories"target="_blank">Github - @JMTS</a>
			</p>'
        </footer>
    </body>

</html>