# Projeto Cliente-servidor 

**Alunos**:<br>
   <li>Erick Giffoni - 170141161<br>
   <li>Geise Saunier - 190124318<br><br>

## simple-tcp

O objetivo é uma aplicação TCP, para diálogo cliente/servidor, para diálogo <br>
bidirecional, cujo lado servidor permaneça com a conexão ativa até que o cliente<br>
informe ao servidor que não há mais nada a enviar; quando isso ocorrer, apenas <br>
o cliente encerra a conexão, mas o servidor deve continuar ativo, aguardando novas conexões.<br>

Temos 2 códigos, representando, respectivamente, cliente e servidor:

<li><a href="./tcpClient.c">tcpClient.c</a><br>
<li><a href="./tcpServer.c">tcpServer.c</a><br>

**Executando**

1. Compile os códigos com o comando ```$ gcc <arquivo>.c -o <arquivo>.out```, em que<br>
"arquivo" representa o nome do arquivo o qual você está compilando.

2. Execute, primeiramente, o servidor. Para isso você precisará informar o IP e<br>
a porta para esse servidor. (Dica: utilize *loopback* 127.0.0.1).

```$ ./<servidor>.out 127.0.0.1 1122```

3. Em seguida, execute o cliente. Nesse caso você precisa informar o IP e a porta<br>
do servidor que está em execução !

```$ ./<cliente>.out 127.0.0.1 1122```

**Uso**


- Para encerrar a conexão com o servidor, o cliente precisa enviar a mensagem<br>
```disconnect```;

- Por meio da função ```listen()```, o servidor é capaz de montar uma fila<br>
para atender os clientes. Dessa forma ele atende um por vez, então os que estão<br>
na fila podem até enviar mensagens, mas elas só serão exibidas pelo servidor<br>
quando o cliente da vez se desconctar. Então automaticamente o servidor mostra<br>
as mensagens enviadas do próximo cliente na fila e passa a o atender;<br>

- É possível que tanto cliente quanto servidor enviem mensagens. Por decisão arbitrária,<br>
o padrão é: o cliente é o detentor da vez de enviar mensagens; para que o servidor<br>
possa enviar a mensagem, o cliente precisa mandar a frase ```over```, então o<br>
servidor entende que está na vez dele. Quando o servidor quer dar a vez de volta<br>
para o cliente, basta enviar ```over```, e assim sucessivamente;<br>

- Para encerrar a execução do servidor, tecle CTRL + C.<br>

**Limitações**


<li>O tamanho da mensagem a ser enviada e a ser recebida está definido como<br>
```BUFFER_SIZE```, cujo valor é 140 caracteres;<br>

<li>O número de clientes a serem atendidos está definido como ```NUMBER_OF_CLIENTS```,<br>
cujo valor é 5.<br>