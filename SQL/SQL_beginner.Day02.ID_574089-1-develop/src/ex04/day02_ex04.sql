select m.pizza_name as pizza_name, pz.name as pizzeria_name, m.price as price
from menu as m
join pizzeria as pz
on m.pizzeria_id = pz.id
where m.pizza_name = 'pepperoni pizza' or m.pizza_name = 'mushroom pizza'
order by 1, 2