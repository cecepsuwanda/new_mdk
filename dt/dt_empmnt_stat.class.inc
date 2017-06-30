<?php require_once('shared.php');
     
class dt_empmnt_stat
{
   private $tb_;
   
   
   function __construct() {
	$this->tb_ = new tb_gen('dbo_empmnt_stat');
   $this->tb_->sql_orderby='no_urut_empmnt';
   }

   function getdata($where)
   {
      return $this->tb_->getData($where);
   }

   function getnm1($kd)
   {
      $data = $this->getdata("Kd_emp='$kd'");
      return empty($data) ? '' : $data[0]['Nm_emp_ind'];
   }

   function getnumrows()
   {
   	  return $this->tb_->numrows;
   }
   
   function getnm($where,$isjumlah=1)
   {
	  $data = $this->getdata($where);	  
	  $tmp=array();
	  if(!empty($data)){
			foreach($data as $row)
			{
				$tmp[]=array(strtoupper($row['Nm_emp_ind']),array()); 
			}
			if($isjumlah==1){
			 $tmp[]=array('JUMLAH',array());
			} 
		}		
	  return $tmp;	
   }
}
