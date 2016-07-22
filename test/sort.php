<?php

    $array = [3, 5, 2, 6, 4];
    
    function selection($array)
    {
        for ($i=0; $i<count($array)-1; $i++)
        {
            $smallest = $array[$i];
            $position = $i;
            for($j=$i+1; $j<count($array); $j++)
            {
                if($array[$j]<$smallest)
                {
                    $smallest = $array[$j];
                    $position = $j;
                }
            }
            $temp = $array[$i];
            $array[$i] = $smallest;
            $array[$position] = $temp;
        }
        return $array;
    };
    
    $sort_array = selection($array);
    
    print_r($sort_array);
?>