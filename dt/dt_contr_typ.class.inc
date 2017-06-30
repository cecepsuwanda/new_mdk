<?php require_once('shared.php');
     
class dt_contr_typ
{
   private $tb_;
   function __construct() {
	$this->tb_ = new tb_gen('dbo_contr_typ');
   }

    function getdata($where)
   {
      return $this->tb_->getData($where);
   }

   function getnm1($kd)
   {
     $data = $this->getdata("Kd_contyp=$kd");
     return isset($data[0]['Nm_contyp_ind']) ? $data[0]['Nm_contyp_ind'] : ''; 
   }

   function getnumrows()
   {
   	  return $this->tb_->numrows;
   }

   function getnm($where,$isjumlah=1,$istotal=0,$isprosen=0,$tmp=array(),$attr=array())
   {
	  
     $data = $this->getdata($where);	  
	  if(!empty($data)){
			foreach($data as $row)
			{
				$tmp[]=array(strtoupper($row['Nm_contyp_ind']),$attr);
            if($isprosen==1){
              $tmp[]=array('%',$attr); 
            }
			}
			if($isjumlah==1){
			 $tmp[]=array('JUMLAH',$attr);
			} 
         if($istotal==1){
          $tmp[]=array('TOTAL',$attr);
         }
		}		
	  return $tmp;	
   }

}

?>   