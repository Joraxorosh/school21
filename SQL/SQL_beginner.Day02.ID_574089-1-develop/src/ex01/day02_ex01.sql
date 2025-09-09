select generate_series::DATE as missing_date
from generate_series('2022-01-01'::date,'2022-01-10'::date,'1 day'::interval)
left join (select *
		   from person_visits
           where person_id = 1 or person_id = 2) as t1
on generate_series = t1.visit_date
where t1.visit_date is null
order by missing_date;