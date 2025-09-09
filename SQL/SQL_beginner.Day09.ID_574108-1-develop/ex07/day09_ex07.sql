create or replace function func_minimum(arr NUMERIC[])
returns NUMERIC as $$
declare
    min_value NUMERIC := arr[1];
    num NUMERIC;
begin
    foreach num in ARRAY arr loop
        if num < min_value then
            min_value := num;
        end if;
    end loop;
    return min_value;
end;
$$ language plpgsql;



--select func_minimum(VARIADIC ARRAY[10.0, -1.0, 5.0, 4.4]);

select func_minimum(ARRAY[10.0, -1.0, 5.0, 4.4]);