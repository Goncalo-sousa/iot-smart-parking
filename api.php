<?php

header('Content-Type: text/html; charset=utf-8');
//echo ($_SERVER['REQUEST_METHOD']);

if ($_SERVER['REQUEST_METHOD'] == "POST") {
	/*mostre a mensagem com POST*/
	//echo "recebido um POST";
	print_r($_POST);
	if (isset($_POST['filename'])) {
		if ($_POST['filename'] == 'lugares'){
		
			file_put_contents("files/" . "lugares" . "/valor.txt",$_POST['valor']);
		}elseif($_POST['filename'] == 'matricula'){

			file_put_contents("files/" . "lugares" . "/mat.txt", $_POST['valor']);
		}elseif($_POST['filename'] == 'portao'){

			file_put_contents("files/" . "lugares" . "/portao.txt", $_POST['valor']);
		}
	} else {
		echo "erro: INVALIDO";
	}
	exit();
} elseif ($_SERVER['REQUEST_METHOD'] == "GET") {

	/*mostre a mensagem com GET*/
	echo file_get_contents("files/lugares/portao.txt");
	exit();
} else {

	/*http_response_code(403)*/
	echo "metodo nao permitido";
	exit();
}
?>
