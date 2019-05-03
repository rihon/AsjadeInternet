
<?php
    // DEFINE VARIABLES
    date_default_timezone_set("Europe/Tallinn");
    $temperatuur = $_REQUEST["temperatuur"];
    $niiskus = $_REQUEST["niiskus"];
    $valgus = $_REQUEST["valgus"];
    $pNiiskus = $_REQUEST["pNiiskus"];
    $taimeKorgus = $_REQUEST["taimeKorgus"];
    $done = $_REQUEST["done"];
    $currentTimeinSeconds = time();
    // converts the time in seconds to current date  
    $currentDate = date('Y/m/d H:i:s', $currentTimeinSeconds); 

    //TURN ON WATERING MOTOR
    if($done == "true"){
        $file = 'mootor.txt';
        // Open the file to get existing content
        $current = file_get_contents($file);
        // Append a new person to the file
        $current = "false";
        // Write the contents back to the file
        file_put_contents($file, $current);
    }
    
    //WRITE DATA TO FILE
    if (isset($temperatuur) and isset($niiskus) and isset($valgus) and isset($pNiiskus) and isset($taimeKorgus)){
        $f=fopen("asjadeInternet.txt", "a");
        fwrite($f, floatval($temperatuur).";".floatval($niiskus).";".floatval($valgus).";".floatval($pNiiskus).";"
        .floatval($taimeKorgus).";".($currentDate)."\n");
        fclose($f);
        echo "Salvestati $temperatuur, $niiskus, $valgus, $pNiiskus, $taimeKorgus"; 
    } else {
        echo "Andmed puuduvad";
    }
?>