bool setup_bluetooth() {
  Serial.begin(9600);
  Serial.println("Bluetooth now active");

  return 0;
}

char check_bluetooth(char seq) {
  if (Serial.available() > 0) {
    Serial.println("Config opened");
    Serial.println("Only 1, 2, 3 are valid for now. Any others will result in the default of 0.");
    Serial.println("Except for X. X is the emergency stop trigger, which kills the sequence thread.");
    seq = Serial.read();
    if (seq == 'X')
      estop_bluetooth();
    Serial.write("Sequence ");
    Serial.write(seq);
    Serial.write(" set. Will start when current sequence finishes.\n");
  }
  return seq;
}

void estop_bluetooth() {
  Serial.println("\n\n***EMERGENCY STOP INITATED***");
  Serial.println("Hard-reset device to re-enable.");
  for (int i = 0; i < NUM; ++i)
    digitalWrite(valve[i], LOW);
  while(1);
}
