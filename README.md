# Envia-Dados-Sensor

Código executado no ESP32 para realizar as leituras do sendor AS7341 e enviar para a planilha do google sheets via WI-FI

#### Script executado para enviar os dados do Sensor AS7341 para a planilha [SENSOR](https://docs.google.com/spreadsheets/d/1RCYBbdXH1hzrEg2qwlLmCxcVZYAFwF5VYIUPBIEIHHk/edit?gid=0#gid=0)

```js
function doGet(e) {
  var sheet = SpreadsheetApp.openById("1RCYBbdXH1hzrEg2qwlLmCxcVZYAFwF5VYIUPBIEIHHk").getSheetByName("SENSOR");
  var ultimaLinha = sheet.getLastRow() + 1;
  var agora = new Date();

  sheet.getRange("A" + ultimaLinha).setValue(agora.toLocaleDateString());
  sheet.getRange("B" + ultimaLinha).setValue(agora.toLocaleTimeString()); 
  sheet.getRange("C" + ultimaLinha).setValue(e.parameter.F1);
  sheet.getRange("D" + ultimaLinha).setValue(e.parameter.F2);
  sheet.getRange("E" + ultimaLinha).setValue(e.parameter.F3);
  sheet.getRange("F" + ultimaLinha).setValue(e.parameter.F4);
  sheet.getRange("G" + ultimaLinha).setValue(e.parameter.F5);
  sheet.getRange("H" + ultimaLinha).setValue(e.parameter.F6);
  sheet.getRange("I" + ultimaLinha).setValue(e.parameter.F7);
  sheet.getRange("J" + ultimaLinha).setValue(e.parameter.F8);
  return ContentService.createTextOutput("Registrado");
}
```