# Controlador de Temperatura (HISTERESE E PROPORCIONAL)

* **Descrição geral do Sistema:**
O sistema de controle possui 2 modos de operação. O primeiro deles é o Modo Controlador ON/OFF, controlando o sistema com histerese. O segundo modo é o Modo Controlador Proporcional, controlando o sistema através do sinal de erro. O sistema possui uma interface composta por display 16x2, 4 botões (P | - | + | S) e o driver de saída. 

* **Periféricos:**
   * **Sensor:** O Sensor de temperatura utilizado é o sensor analógico LM35.
   * **MCU:** O MCU escolhido para o desenvolvimento foi o ATMega328p (Arduino) e ele é o responsável pelas tarefas de controle e interface do sistema. 
   * **Driver:** O driver do controlador é composto um único transistor do tipo MOSFET ligado no componente virtual OVEN do Proteus.

* **Software:**
O software foi desenvolvido utilizando a IDE PLatformIO com o Visual Studio Code.
   * **Bibliotecas utilizadas:** LiquidCrystal
   * **Definições:** O arquivo */include/definitions.h* contém todas as definições de parâmetros de execução, pinos de GPIO e parâmetros iniciais do controlador.
   * **Arquivo .hex:** Ao compilar a aplicação, os arquivos .hex e .elf ficam localizados na pasta escondida **.pio/build/uno/[uno_LINUX ou uno_WINDOWS]**. 

## Controlador ON/OFF de Temperatura (Histerese)
* **Descrição geral do Sistema:**
O controle é realizado com histerese (dead band) e a configuração de alguns parâmetros do sistema é feita através da interface de usuário. Sâo elas:
   * Novo set-point.
   * Valor de histerese para ligar o driver.
   * Valor de histerese para desligar o driver.
   * Desabilitar o controlador independentemente da temperatura

<div align="center">
   <img src="README_MEDIAS/diagrama_blocos_sistema_hyst.png" alt="diagrama" width="50%" height="20%"/></center>
</div>

* **Funcionamento:**
   O sistema se inicializa na tela de supervisório. Nela é possível observar o estado atual do controlador, os valores mínimo e máximo de histerese, o valor atual da temperatura e o setpoint configurado. Ao clicar no botão P, o sistema entra no modo de configuração. Nesse modo é possível percorrer 3 telas, sendo elas a configuração da porcentagem de histerese, o estado atual da saída para o driver e o setpoint desejado. Para alternar entre as telas, os botões LEFT(-) e RIGHT(+) são utilizados. Para editar alguma configuração de alguma tela, dar um clique simples no botão S e o valor pode ser alterado através das teclas laterais. Para salvar a configuração, clicar no botão S novamente. Para sair do modo de configuração e retornar para a tela supervisória, clicar no botão P.

## Controlador Proporcional de Temperatura
* **Descrição geral do Sistema:**
O controle é realizado proporcionalmente. Portanto, o sinal de erro (diferença entre o sinal de referência e o sinal de realimentação) é multiplicado pelo ganho
proporcional (Kp) e aplicado na saída. Para isso, as telas disponíveis no modo programação são as seguintes:
   * Novo set-point.
   * Ajuste de ganho proporcional (Kp)
   * Estado do modo manual do aquecedor
   * Valor do modo manual do aquecedor
   * Estado do modo manual do ventilador
   * Valor do modo manual do ventilador
   * Desabilitar o driver de saída

<div align="center">
   <img src="README_MEDIAS/diagrama_blocos_sistema_prop.png" alt="diagrama" width="50%" height="20%"/></center>
</div>

* **Funcionamento:**
   O sistema se inicializa na tela de supervisório. Nela é possível observar o estado atual do controlador, os valores de setpoint e de temperatura atual, além do estado dos periféricos. Ao clicar no botão P, o sistema entra no modo de configuração. Nesse modo é possível percorrer 6 telas, sendo elas a ativação do driver de saída, o valor de setpoint, o valor do ganho proporcional, a porcentagem de saída PWM do aquecedor quando ligado manualmente, a ativação manual do aquecedor, o estado a porcentagem de saída PWM do ventilador quando ligado manualmente e a ativação manual do ventilador aquecedor. Para alternar entre as telas, os botões LEFT(-) e RIGHT(+) são utilizados. Para editar alguma configuração de alguma tela, dar um clique simples no botão S e o valor pode ser alterado através das teclas laterais. Para salvar a configuração, clicar no botão S novamente. Para sair do modo de configuração e retornar para a tela supervisória, clicar no botão P.

## Trabalhos Futuros:
   * Armazenar os parâmetros do sistema na EEPROM para que não seja preciso uma nova configuração à cada inicialização.
   * Apresentar na MAINPAGE do controlador proporcional as saídas individuais de aquecedor e ventilador.

## Montagem Física do Sistema:
<div align="center">
   <img src="README_MEDIAS/montagem_fisica_sistema.jpeg" alt="diagrama" width="50%" height="20%"/></center>
</div>