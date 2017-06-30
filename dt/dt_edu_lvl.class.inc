<?php require_once('shared.php');
     
class dt_edu_lvl
{
   private $tb_;
   function __construct() {
	$this->tb_ = new tb_gen('dbo_edu_lvl');
   $this->tb_->sql_orderby = 'no_urut';
   }

   function getnm1($kd)
   {
      $data = $this->getdata("Kd_edu='$kd'");
      return empty($data) ? array() : $data[0]['Nm_edu_ind'];
   }

    function getdata($where)
   {
      return $this->tb_->getData($where);
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
				$tmp[]=array(strtoupper($row['Nm_edu_ind']),array()); 
			}
			if($isjumlah==1){
			 $tmp[]=array('JUMLAH',array());
			} 
		}		
	  return $tmp;	
   }

}

?>   