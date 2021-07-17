<?php
header('Content-Type: text/html; charset=utf-8');
#$target_dir = "/files/lugares/";
#$target_file = $target_dir . basename($_FILES["image"]["name"]);

$uploaddir = './files/lugares/';
$uploadfile = $uploaddir . basename($_FILES['userfile']['name']);

if ($_SERVER["REQUEST_METHOD"] == "POST") {
	echo '<pre>';
	if (move_uploaded_file($_FILES['userfile']['tmp_name'], $uploadfile)) {
    		echo "File is valid, and was successfully uploaded.\n";
	} else {
   		 echo "Possible file upload attack!\n";
	}

	echo 'Here is some more debugging info:';
	print_r($_FILES);
	print "</pre>";

}
?>
