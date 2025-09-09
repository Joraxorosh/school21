select p.name, count(p.name) as count_of_orders, round(avg(m.price), 2) as average_price, max(m.price) as max_price, min(m.price) as min_price
from person_order as po
join menu as m
	on m.id = po.menu_id
join pizzeria as p 
	on p.id = m.pizzeria_id
group by p.name
order by p.name;