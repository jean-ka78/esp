BLYNK_WRITE(V51){
  lux_in = param.asInt();
  // DATA_Send();
  
}
BLYNK_WRITE(V52){
  lux_on = param.asInt();
  // DATA_Send();
}

void svet()
{
    if (lux_on==1)
    {
        if (lux<lux_in)
        {
            lux_relley = 1;
//             terminal.println(lux_relley);
//       terminal.flush();
        }
        else
        {
            lux_relley = 0;
//             terminal.println(lux_relley);
//       terminal.flush();
        }
               
    }
    else
    {
        lux_relley = 0;
//         terminal.println(lux_relley);
//       terminal.flush();
    }
    
    
} 
