//Solar Tracker

#include <Fuzzy.h>
#include <FuzzyComposition.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzyOutput.h>
#include <FuzzyRule.h>
#include <FuzzyRuleAntecedent.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzySet.h>

#include <Servo.h>

#define ldr_0 0
#define ldr_1 1
#define ldr_2 2
#define ldr_3 3

int ldrValue_0,
    ldrValue_1,
    ldrValue_2,
    ldrValue_3,
    T = 100;
float pos1 = 90,
      pos2 = 90;

unsigned long temp = 0;

Servo servo1;
Servo servo2;



Fuzzy* fuzzy = new Fuzzy();    //Objeto que armazena todos os componentes do sistema Fuzzy

void configuracaoFuzzy(){
  //Criando a variÃ¡vel de entrada diferenca1
  FuzzyInput* diferenca1 = new FuzzyInput(1);
 
  //Criando a variÃ¡vel de entrada diferenca2
  FuzzyInput* diferenca2 = new FuzzyInput(2);

  //Criando a variÃ¡vel de saÃ­da Motor1
  FuzzyOutput* motor1 = new FuzzyOutput(1);

  //Criando a variÃ¡vel de saÃ­da Motor2
  FuzzyOutput* motor2 = new FuzzyOutput(2);
 
  //Modelagem das variaveis
  
  FuzzySet* altomenos = new FuzzySet(-1000,-1000, -400, -300);
  FuzzySet* baixomenos = new FuzzySet(-400, -300, -200, -25); 
  FuzzySet* tolerancia = new FuzzySet(-50, -0, 0, 50);
  FuzzySet* baixomais = new FuzzySet(25, 200, 300, 400);
  FuzzySet* altomais = new FuzzySet(300, 400, 1000, 1000);
  
  FuzzySet* muitonegativo = new FuzzySet(-10,-10,-7.5,-2.5);
  FuzzySet* pouconegativo = new FuzzySet(-7.5, -5, -2.5, 0);
  FuzzySet* parado = new FuzzySet(0, 0, 0, 0);
  FuzzySet* poucopositivo = new FuzzySet(0, 2.5, 5, 7.5);
  FuzzySet* muitopositivo = new FuzzySet(2.5, 7.5, 10, 10);
  
  FuzzySet* altomenos2 = new FuzzySet(-1000,-1000, -400, -300);
  FuzzySet* baixomenos2 = new FuzzySet(-400, -300, -200, -25); 
  FuzzySet* tolerancia2 = new FuzzySet(-100, -0, 0, 100);
  FuzzySet* baixomais2 = new FuzzySet(25, 200, 300, 400);
  FuzzySet* altomais2 = new FuzzySet(300, 400, 1000, 1000);    

  
  FuzzySet* muitonegativo2 = new FuzzySet(-10,-10,-7.5,-2.5);  
  FuzzySet* pouconegativo2 = new FuzzySet(-7.5, -5, -2.5, 0);
  FuzzySet* parado2 = new FuzzySet(0, 0, 0, 0);
  FuzzySet* poucopositivo2 = new FuzzySet(0, 2.5, 5, 7.5);
  FuzzySet* muitopositivo2 = new FuzzySet(2.5, 7.5, 10, 10);
 
  //Estados PossÃ­veis
  diferenca1->addFuzzySet(baixomais);
  diferenca1->addFuzzySet(altomais);
  diferenca1->addFuzzySet(baixomenos);
  diferenca1->addFuzzySet(altomenos);
  diferenca1->addFuzzySet(tolerancia);
  
  diferenca2->addFuzzySet(baixomais2);
  diferenca2->addFuzzySet(altomais2);
  diferenca2->addFuzzySet(baixomenos2);
  diferenca2->addFuzzySet(altomenos2);
  diferenca2->addFuzzySet(tolerancia2);
  
  motor1 ->addFuzzySet(pouconegativo);
  motor1 ->addFuzzySet(muitonegativo);
  motor1 ->addFuzzySet(parado);
  motor1 ->addFuzzySet(poucopositivo);
  motor1 ->addFuzzySet(muitopositivo);
  
  motor2 ->addFuzzySet(pouconegativo2);
  motor2 ->addFuzzySet(muitonegativo2);
  motor2 ->addFuzzySet(parado2);
  motor2 ->addFuzzySet(poucopositivo2);
  motor2 ->addFuzzySet(muitopositivo2);
  
  //Inclui a FuzzyInput no objeto Fuzzy
  fuzzy->addFuzzyInput(diferenca1);
  fuzzy->addFuzzyInput(diferenca2);
  fuzzy->addFuzzyOutput(motor1);
  fuzzy->addFuzzyOutput(motor2);


  //Rules
  FuzzyRuleAntecedent* ifaltomenos2 = new FuzzyRuleAntecedent();
  ifaltomenos2->joinSingle(altomenos2);
  FuzzyRuleConsequent* entaoMuitoPositivo2 = new FuzzyRuleConsequent();
  entaoMuitoPositivo2->addOutput(muitopositivo2);
  FuzzyRule* fuzzyRule01 = new FuzzyRule(2, ifaltomenos2, entaoMuitoPositivo2);
  fuzzy->addFuzzyRule(fuzzyRule01);

  FuzzyRuleAntecedent* ifbaixomenos2 = new FuzzyRuleAntecedent();
  ifbaixomenos2->joinSingle(baixomenos2);
  FuzzyRuleConsequent* entaoPoucoPositivo2 = new FuzzyRuleConsequent();
  entaoPoucoPositivo2->addOutput(poucopositivo2);
  FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifbaixomenos2, entaoPoucoPositivo2);
  fuzzy->addFuzzyRule(fuzzyRule02);

  FuzzyRuleAntecedent* ifTolerancia2 = new FuzzyRuleAntecedent();
  ifTolerancia2->joinSingle(tolerancia2);
  FuzzyRuleConsequent* entaoParado2 = new FuzzyRuleConsequent();
  entaoParado2->addOutput(parado2);
  FuzzyRule* fuzzyRule03 = new FuzzyRule(2, ifTolerancia2, entaoParado2);
  fuzzy->addFuzzyRule(fuzzyRule03);

  FuzzyRuleAntecedent* ifbaixomais2 = new FuzzyRuleAntecedent();
  ifbaixomais2->joinSingle(baixomais2);
  FuzzyRuleConsequent* entaoPoucoNegativo2 = new FuzzyRuleConsequent();
  entaoPoucoNegativo2->addOutput(pouconegativo2);
  FuzzyRule* fuzzyRule04 = new FuzzyRule(2, ifbaixomais2, entaoPoucoNegativo2);
  fuzzy->addFuzzyRule(fuzzyRule04);

  FuzzyRuleAntecedent* ifaltomais2 = new FuzzyRuleAntecedent();
  ifaltomais2->joinSingle(altomais2);
  FuzzyRuleConsequent* entaoMuitoNegativo2 = new FuzzyRuleConsequent();
  entaoMuitoNegativo2->addOutput(muitonegativo2);
  FuzzyRule* fuzzyRule05 = new FuzzyRule(2, ifaltomais2, entaoMuitoNegativo2);
  fuzzy->addFuzzyRule(fuzzyRule05);

  FuzzyRuleAntecedent* ifaltomenos = new FuzzyRuleAntecedent();
  ifaltomenos->joinSingle(altomenos);
  FuzzyRuleConsequent* entaoMuitoPositivo = new FuzzyRuleConsequent();
  entaoMuitoPositivo->addOutput(muitopositivo);
  FuzzyRule* fuzzyRule06 = new FuzzyRule(1, ifaltomenos, entaoMuitoPositivo);
  fuzzy->addFuzzyRule(fuzzyRule06);

  FuzzyRuleAntecedent* ifbaixomenos = new FuzzyRuleAntecedent();
  ifbaixomenos->joinSingle(baixomenos);
  FuzzyRuleConsequent* entaoPoucoPositivo = new FuzzyRuleConsequent();
  entaoPoucoPositivo->addOutput(poucopositivo);
  FuzzyRule* fuzzyRule07 = new FuzzyRule(1, ifbaixomenos, entaoPoucoPositivo);
  fuzzy->addFuzzyRule(fuzzyRule07);

  FuzzyRuleAntecedent* ifTolerancia = new FuzzyRuleAntecedent();
  ifTolerancia->joinSingle(tolerancia);
  FuzzyRuleConsequent* entaoParado = new FuzzyRuleConsequent();
  entaoParado->addOutput(parado);
  FuzzyRule* fuzzyRule08 = new FuzzyRule(1, ifTolerancia, entaoParado);
  fuzzy->addFuzzyRule(fuzzyRule08);

  FuzzyRuleAntecedent* ifbaixomais = new FuzzyRuleAntecedent();
  ifbaixomais->joinSingle(baixomais);
  FuzzyRuleConsequent* entaoPoucoNegativo = new FuzzyRuleConsequent();
  entaoPoucoNegativo->addOutput(pouconegativo);
  FuzzyRule* fuzzyRule09 = new FuzzyRule(1, ifbaixomais, entaoPoucoNegativo);
  fuzzy->addFuzzyRule(fuzzyRule09);

  FuzzyRuleAntecedent* ifaltomais = new FuzzyRuleAntecedent();
  ifaltomais->joinSingle(altomais);
  FuzzyRuleConsequent* entaoMuitoNegativo = new FuzzyRuleConsequent();
  entaoMuitoNegativo->addOutput(muitonegativo);
  FuzzyRule* fuzzyRule10 = new FuzzyRule(1, ifaltomais, entaoMuitoNegativo);
  fuzzy->addFuzzyRule(fuzzyRule10);
  
  
  
}



void setup() {
  configuracaoFuzzy();
  servo1.attach(9);
  servo2.attach(10);
  Serial.begin(115200);
}

void loop() {


  if((millis() - temp) >= T){
   
    temp = millis();
    
    ldrValue_0 = analogRead(ldr_0);
    ldrValue_1 = analogRead(ldr_1);
    ldrValue_2 = analogRead(ldr_2);
    ldrValue_3 = analogRead(ldr_3);

    int diferenca1 = ((ldrValue_0 - ldrValue_1) + (ldrValue_3 - ldrValue_2))/2;
    int diferenca2 = ((ldrValue_0 - ldrValue_3) + (ldrValue_1 - ldrValue_2))/2;

  
    fuzzy->setInput(1, diferenca1);
    fuzzy->setInput(2, diferenca2);

    fuzzy-> fuzzify();

    float output1 = fuzzy->defuzzify(1);
    float output2 = fuzzy->defuzzify(2);

    pos1 = pos1 + output1;
    pos2 = pos2 + output2;
  
    if(pos1 > 160) {pos1 = 160;}
    if(pos1 < 10) {pos1 = 10;}
    if(pos2 > 160) {pos2 = 160;}
    if(pos2 < 10) {pos2 = 10;}

    servo1.write(pos1);
    servo2.write(pos2);

  }
}

