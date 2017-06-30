<?php require_once('shared.php');

class arraymuldim
{
  private $main_array;
  private $level;
  private $idx;
  private $ckey;  

  function __construct() {
	$this->init();			
  }
  
  private function init()
  {
  	$this->main_array = array();	
	$this->level=0;
	$this->idx=array();
	$this->idx[$this->level]=0;
	$this->ckey=array();
	$this->ckey[$this->level]=null;
  }
  
  private function trans_array(&$array,$level,$key,$val)
  {
    if($level==$this->level)
    {
      
	    if(!is_null($val) and !is_null($key))
        {         
           $array[$key]=$val; 
        }elseif (!is_null($val)) {
           $array[]=$val;          
        }

    }else{      
      if(($this->ckey[$level]==null) and isset($array[$this->idx[$level]-1])){ 
	   $this->trans_array($array[$this->idx[$level]-1],$level+1,$key,$val);      
      }else{
	   $this->trans_array($array[$this->ckey[$level]],$level+1,$key,$val);	  
	  }
	}            
  }

  public function add($val=null,$key=null)
  {
    
    $this->trans_array($this->main_array,0,$key,$val);    

    $this->idx[$this->level]++;
	$this->ckey[$this->level]=$key;

    if(!is_null($val) and is_array($val)){
    	$this->level++;
    	$this->idx[$this->level]=0;
    }
    return $this;
  }

  public function sub($key=null)
  {
    $this->add(array(),$key);
	$this->ckey[$this->level]=$key;
  	return $this;
  }

  public function lsub($jml=1)
  {
    for($i=1;$i<=$jml;$i++){
     $this->add(array());
    }

  	return $this;
  }
  
  public function nextlevel()
  {
    $level = $level+1;
    return $this;
  }

  public function prevlevel($subs=1)
  {
    
    $this->level = ($this->level-$subs)>0 ? $this->level-$subs : 0;
    return $this;	
  }   

  public function nextindex()
  {

  }

  public function previndex()
  {
  	
  }

  public function emptyarray()
  {
  	if(!empty($this->main_array)){
       unset($this->main_array);
       $this->init();       
  	}  
  }

  public function getarray()
  {
  	return $this->main_array;
  }


}

	