create view v_price_with_discount as
select p.name, m.pizza_name, m.price, (m.price - m.price * 0.1) as discount_price
from person_order as po
join person as p 
	on p.id = po.person_id
join menu as m 
	on m.id = po.menu_id
order by 1, 2