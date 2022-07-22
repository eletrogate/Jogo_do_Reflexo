#define LED_ESQ 11 // A porta do LED esquerdo
#define LED_DIR 9 // A porta do LED direito

#define BT_ESQ 7 // A porta do botão esquerdo
#define BT_DIR 5 // A porta do botão esquerdo

#define PWM_MAX 255 // O valor máximo de saídas PWM
#define PWM_MIN 0 // O valor mínimo de saídas PWM

#define TEMPO_MIN 1000 // O intervalo mínimo do tempo de espera
#define TEMPO_MAX 7000 // O intervalo máximo do tempo de espera
#define FLASH 150 // Atraso para piscar os LEDs

void setup() {
  // Configuração dos pinos, definir o que é entrada e saída
  pinMode(LED_ESQ, OUTPUT);
  pinMode(LED_DIR, OUTPUT);
  pinMode(BT_ESQ, INPUT);
  pinMode(BT_DIR, INPUT);
  Serial.begin(9600);
  Serial.println("----------");
  Serial.println("ELETROGATE");
  Serial.println("----------");
  Serial.println("");
  Serial.println("Jogo do reflexo");
  Serial.println("(っ▀¯▀)つ");
  Serial.println("");
  
  delay(1000);

  // Acender os leds
  byte pwAtual = PWM_MAX;
  analogWrite(LED_ESQ, pwAtual);
  analogWrite(LED_DIR, pwAtual);
  
  Serial.println("Começando em 3...");
  delay(1000);
  Serial.println("             2");
  delay(1000);
  Serial.println("             1");
  
  // Apagar os LEDs suavemente em aproximadamente 1 segundo
  while(pwAtual > 0) {
    pwAtual -= 17; // A cada loop, reduzir a potência em 17, assim em 15 ciclos os LEDs se apagarão
    analogWrite(LED_ESQ, pwAtual);
    analogWrite(LED_DIR, pwAtual);
    delay(66);
  }
}

void loop() {
  Serial.println("");
  Serial.print("Aguarde...");
  unsigned int tempoRandomico = random(TEMPO_MIN, TEMPO_MAX); // Gerar o tempo de espera aleatório
  delay(tempoRandomico); // Aguardar o tempo aleatório
  unsigned long millisInicial = millis(); // Salvar o tempo inicial
  unsigned long millisEsq;
  unsigned long millisDir;
  bool btEsqPressionado = false;
  bool btDirPressionado = false;
  bool ledEsqAceso = false;
  bool ledDirAceso = false;
  Serial.print("Pressione seu botão!!!");
  while (!btEsqPressionado || !btDirPressionado) { // Loop para executar enquanto os botões não forem pressionados
    if (digitalRead(BT_ESQ) && !btEsqPressionado) { // Verficar se o botão esquerdo foi pressionado, mas só na primeira vez
      btEsqPressionado = true; // Salvar que o botão foi pressionado
      millisEsq = millis(); // Salvar o tempo em que o botão esquerdo foi pressionado
      analogWrite(LED_ESQ, PWM_MIN); // Apagar o LED esquerdo
    }

    if (digitalRead(BT_DIR) && !btDirPressionado) { // Verficar se o botão direito foi pressionado, mas só na primeira vez
      btDirPressionado = true; // Salvar que o botão foi pressionado
      millisDir = millis(); // Salvar o tempo em que o botão direito foi pressionado
      analogWrite(LED_DIR, PWM_MIN); // Apagar o LED direito
    }

    if (millis() - millisInicial > FLASH) { // Condição para apagar ou acender os LEDs fazendo-os piscarem
      if (!btEsqPressionado) { // O LED esquerdo só pisca se o botão esquerdo ainda não foi pressionado
        if (ledEsqAceso) {
          analogWrite(LED_ESQ, PWM_MIN);
        }
        else {
          analogWrite(LED_ESQ, PWM_MAX);
        }

        ledEsqAceso = !ledEsqAceso; // Apagar se estiver aceso e acender se estiver apagado
      }
      
      if (!btDirPressionado) { // O LED direito só pisca se o botão direito ainda não foi pressionado
        if (ledDirAceso) {
          analogWrite(LED_DIR, PWM_MIN);
        }
        else {
          analogWrite(LED_DIR, PWM_MAX);
        }

        ledDirAceso = !ledDirAceso; // Apagar se estiver aceso e acender se estiver apagado
      }
    }
  }

  Serial.println("Que rufem os tambores!"); // Suspense
  delay(2000);
  Serial.println("");

  if (millisEsq != millisDir) { // Verificar se não houve empate
    Serial.print("O botão ");
    if (millisEsq < millisDir) { // Verfiricar se o botão esquerdo foi pressionado mais rapidamente
      Serial.print("esquerdo");
      analogWrite(LED_ESQ, PWM_MAX); // Acender led esquerdo indicando vencedor
    }
    else {
      Serial.print("direito");
      analogWrite(LED_DIR, PWM_MAX); // Acender led direito indicando vencedor
    }
    
    Serial.println(" foi pressionado mais rapidamente");
  }
  else {
    Serial.println("Houve um empate! Uau, isso é tão raro...");
  }
  
  Serial.println("");
  delay(1000);
  Serial.println("(っ▀¯▀)つ");
  Serial.println("Parabéns!");
  Serial.println("");
  Serial.println("Tempos:");
  Serial.print("Esquerdo = ");
  Serial.print(millisEsq - millisInicial); // Exibir o tempo demorado para o botão esquerdo ser pressionado
  Serial.println(" ms");
  delay(1000);
  
  Serial.print("Direito = ");
  Serial.print(millisDir - millisInicial); // Exibir o tempo demorado para o botão direito ser pressionado
  Serial.println(" ms");
  delay(1000);
  
  Serial.println("");
  Serial.println("Pressione um botão para jogar de novo");
  Serial.println("");
  // Apagar LEDs
  analogWrite(LED_ESQ, PWM_MIN);
  analogWrite(LED_DIR, PWM_MIN);
  while(!digitalRead(BT_ESQ) && !digitalRead(BT_DIR)) { } // Fazer nada enquanto algum botão não é pressionado
}