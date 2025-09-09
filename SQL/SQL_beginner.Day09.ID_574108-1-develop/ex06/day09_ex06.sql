create or replace function fnc_person_visits_and_eats_on_date(
    pperson VARCHAR DEFAULT 'Dmitriy',
    pprice NUMERIC DEFAULT 500,
    pdate DATE DEFAULT '2022-01-08'
)
returns table(pizzeria_name VARCHAR) as $$
begin
    return query
    select distinct pz.name
    from person_visits as pv
    join person as p 
		on pv.person_id = p.id
    join menu as m 
		on pv.pizzeria_id = m.pizzeria_id
    join pizzeria as pz 
		on pz.id = m.pizzeria_id
    where p.name = pperson and m.price < pprice and pv.visit_date = pdate;
end;
$$ language plpgsql;

--select * from fnc_person_visits_and_eats_on_date(pprice := 800);

select * from fnc_person_visits_and_eats_on_date(pperson := 'Anna', pprice := 1300, pdate := '2022-01-01');