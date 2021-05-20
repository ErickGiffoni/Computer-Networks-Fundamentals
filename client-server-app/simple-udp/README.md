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

- É possível que tanto cliente quanto servidor enviem mensagens. Por decisão arbitrária,<br>
o padrão é: o cliente é o detentor da vez de enviar mensagens; para que o servidor<br>
possa enviar a mensagem, o cliente precisa mandar a frase ```over```, então o<br>
servidor entende que está na vez dele. Quando o servidor quer dar a vez de volta<br>
para o cliente, basta enviar ```over```, e assim sucessivamente;<br>

- O servidor consegue atender mais de um cliente por vez. Entretanto, se um deles<br>
disser ```over```, o servidor para de mostrar as mensagens que podem estar <br>
chegando até que ele mande suas mensagens para o respectivo cliente e depois<br>
```over```.

**Limitações**

<li>O tamanho da mensagem a ser enviada e a ser recebida está definido como<br>
```BUFFER_SIZE```, cujo valor é 140 caracteres.