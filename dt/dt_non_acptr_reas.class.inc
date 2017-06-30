<?php require_once('shared.php');
     
class dt_non_acptr_reas
{
   private $tb_;
   function __construct() {
	$this->tb_ = new tb_gen('dbo_non_acptr_reas');
   }

    function getdata($where)
   {
      return $this->tb_->getData($where);
   }

   function getnm1($kd)
   {
     $data = $this->getdata("Kd_nonacptr=$kd");
     return isset($data[0]['Nm_nonacptr_ind']) ? $data[0]['Nm_nonacptr_ind'] : ''; 
   }

   function getnumrows()
   {
   	  return $this->tb_->numrows;
   }

   function getnm($where,$isjumlah=1,$tmp=array(),$attr=array())
   {
	  $data = $this->getdata($where);	  
	  
	  if(!empty($data)){
			foreach($data as $row)
			{
				$tmp[]=array(strtoupper($row['Nm_nonacptr_ind']),$attr); 
			}
			if($isjumlah==1){
			 $tmp[]=array('JUMLAH',array());
			} 
		}		
	  return $tmp;	
   }

}

?>   