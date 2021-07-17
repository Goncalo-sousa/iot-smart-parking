<?php

$valor_movimento = file_get_contents("./files/lugares/valor.txt");
$valor_matricula = file_get_contents("./files/lugares/mat.txt");
?>


<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="refresh" content="15">


    <title>Dashboard</title>

    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <link rel="stylesheet" href="style.css">
</head>
<nav class="navbar navbar-expand-lg navbar-light bg-light">
    <div class="container-fluid">

        <div class="navbar" id="navbarSupportedContent">
            <ul class="nav navbar-nav ml-auto">
                <li class="nav-item active">
                    <a class="nav-link" href="#">Dashboard</a>
                </li>
                <li class="nav-item active">
                    <a class="nav-link" href="#"></a>
                </li>
            </ul>
        </div>
    </div>
</nav>

<body>
    <br>
    <div class="container">

        <div class="card-deck">

            <div class="card">
                <div class="card-header bg-light text-dark text-center">Ultima Matricula: <?php echo $valor_matricula ?></div>
                <div class="card-body text-center"><img src="./files/lugares/userfile.jpg" width="250" height="250"></div>
            </div>

            <div class="card">
                <div class="card-header bg-light text-dark text-center">Lugares disponiveis: <?php  if ($valor_movimento == 1){echo "Não";}else{echo "Sim";} ?>
                </div>
                <!--<div class="card-body text-center"><img src="motion.png" style="width:50%" class="center">--</div>
            </div>
        </div>
    </div>
    <div class="line"></div>

    </div>
</body>

</html>
