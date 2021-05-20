# Projeto Cliente-servidor 

**Alunos**:<br>
   <li>Erick Giffoni - 170141161<br>
   <li>Geise Saunier - 190124318<br><br>

## simple-udp

O objetivo é uma aplicação UDP simples, cujo fluxo de diálogo entre Cliente e <br>
Servidor seja bidirecional. Ou seja, os dois lados (cliente e servidor) enviam<br>
e recebem mensagens de um para o outro.

Temos 2 códigos, representando, respectivamente, cliente e servidor:

<li><a href="./udpClient.c">udpClient.c</a><br>
<li><a href="./udpServer.c">udpServer.c</a><br>

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

- TODO

**Limitações**

<li>O tamanho da mensagem a ser enviada e a ser recebida está definido como<br>
```BUFFER_SIZE```, cujo valor é 140 caracteres.