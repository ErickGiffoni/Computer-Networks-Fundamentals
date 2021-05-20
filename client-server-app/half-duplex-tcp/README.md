# Projeto Cliente-servidor 

**Alunos**:<br>
   <li>Erick Giffoni - 170141161<br>
   <li>Geise Saunier - 190124318<br><br>

## half-duplex-tcp

O objetivo é uma aplicação TCP, na qual o servidor consiga atender mais de um<br>
cliente ao mesmo tempo, para promover diálogo bidirecional (half-duplex, ou<br>
seja, enquanto um dos lados fala o outro escuta e vice-versa, numa ordem pré-definida),<br>
usando a system call fork(). Vários clientes podem dialogar com o servidor, mas<br>
não entre si.

Temos 2 códigos, representando, respectivamente, cliente e servidor:

<li><a href="./hd-tcpClient.c">hd-tcpClient.c</a><br>
<li><a href="./hd-tcpServer.c">hd-tcpServer.c</a><br>

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
para atender os clientes;

- Quando um novo cliente tenta se conectar, a função ```accept()``` o retira da<br>
fila. Em seguida, é criado um processo filho, por meio da ```fork()```, para que<br>
o cliente seja atendido;

- É possível que tanto cliente quanto servidor enviem mensagens. Por decisão arbitrária,<br>
o padrão é: o cliente é o detentor da vez de enviar mensagens; para que o servidor<br>
possa enviar a mensagem, o cliente precisa mandar a frase ```over```, então o<br>
servidor entende que está na vez dele. Quando o servidor quer dar a vez de volta<br>
para o cliente, basta enviar ```over```, e assim sucessivamente.

**Limitações**


<li>O tamanho da mensagem a ser enviada e a ser recebida está definido como<br>
```BUFFER_SIZE```, cujo valor é 140 caracteres;<br>

<li>O número de clientes a serem atendidos está definido como ```NUMBER_OF_CLIENTS```,<br>
cujo valor é 140.<br>