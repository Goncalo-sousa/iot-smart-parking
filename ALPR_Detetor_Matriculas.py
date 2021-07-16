import cv2
from openalpr import Alpr
import sys
import requests

#Inicializar o ALPR
alpr = Alpr("eu", "home/etc/openalpr/openalpr.conf",
            "/home/amachado/Downloads/openalpr/runtime_data")

if not alpr.is_loaded():
    print("Error loading OpenALPR")
    sys.exit(1)

alpr.set_top_n(3)
alpr.set_default_region('pt')

#Inicializar a camptura de video
cap = cv2.VideoCapture(0)

#Lista de Matriculas que são permitidas de entrar
matriculas=["XQ33XQ","01AS22","24AB35"]


if not cap.isOpened():
    alpr.unload()
    sys.exit('Failed to open video file!')

#Começo do loop do script
while(True):
    portao="0";
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    temp = "frame%d.jpg" % ret
    cv2.imwrite(temp, frame)
    cv2.imshow('frame', gray)
    
    #Envio da frame para o ALPR
    results = alpr.recognize_file(temp)
    
    #Comparação dos resultados
    for plate in results['results']:
        for candidate in plate['candidates']:
            #if candidate["confidence"] >= 90:
            #Comparação das matriculas da lista com as detetadas
            if plate['plate'] in matriculas: 
                print("Matricula Detetada")
                print("    Numero: %s Confiança: %s" % (plate["plate"], candidate["confidence"]))
                cv2.imwrite("webcam.jpg", frame)
                portao="1"
                
                try:
                    
                    #Campos para enviar o valor da matricula
                    url = "http://192.168.137.1:8081/api.php/"
                    headers = {'Content-type': 'application/x-www-form-urlencoded'}
                    body="filename=matricula&valor=" + plate["plate"]
                    bodyPortao="filename=portao&valor=" + portao
                    
                    #Envio e resposta da matricula
                    response = requests.post(url, headers=headers, data=body)
                    print("Post Matricula %s" % response.text )
                    
                    #Campos para o envio da foto da matricula
                    url_files = "http://192.168.137.1:8081/upload.php/"
                    data = {'userfile': ('userfile.jpg', open('webcam.jpg', 'rb'), 'image/jpeg', {'Expires': '0'})}
                    
                    #Envio e resposta da foto
                    response = requests.post(url=url_files, files=data)
                    print("Post Matricula_Foto %s" % response.text)
                    
                    #Envio e reposta do portão
                    response = requests.post(url, headers=headers, data=bodyPortao)
                    print("Abrir Portao: %s" % response.text )
                    
                    
                except (ConnectionError):
                    print("Ligação com a API falhou")
                    
                except:
                    print("Erro na deteção de matricula")
                    
                           
            
                
    # the 'q' button is set as theq
    # quitting button you may use any
    # desired button of your choice
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
  
# After the loop release the cap object
cap.release()
# Destroy all the windows
cv2.destroyAllWindows()
alpr.unload()