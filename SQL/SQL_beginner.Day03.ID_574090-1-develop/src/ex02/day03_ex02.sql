with t1 as (select m.id as menu_id
from menu as m
except
select po.menu_id
from person_order as po)
select m.pizza_name, m.price, pz.name as pizzeria_name
from t1
join menu as m 
	on m.id = t1.menu_id
join pizzeria as pz 
    on pz.id = m.pizzeria_id
order by 1, 2