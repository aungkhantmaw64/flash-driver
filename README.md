# Flash Memory Driver

![Tests](https://github.com/aungkhantmaw64/flash-driver/actions/workflows/test-suite.yml/badge.svg)

## Flash Memory Program Flow Chart

```mermaid
flowchart TD
    id1(Start)
    id2[/Program Command Write 0x40 to 0/]
    id3[/Write data to address/]
    id4[/Read status register/]
    id5{b7==1?}
    id6{b3==0?}
    id7{b4==0?}
    id8{b1==0?}
    id9(End/Start)
    id10[Vpp Error]
    id11[Program Error]
    id12[Protected Block Error]
    id13[/Clear status Write 0xFF to 0x0/]

    id1 --> id2
    id2 --> id3
    id3 --> id4
    id4 --> id5
    id5 --> |No| id4
    id5 --> |Yes| id6
    id6 --> |No| id10
    id6 --> |Yes| id7
    id7 --> |No| id11
    id7 --> |Yes| id8
    id8 --> |No| id12
    id8 --> |Yes| id9
    id10 --> id13
    id11 --> id13
    id12 --> id13

    id13 --> id9

```

<details>
<summary>

## Flash Driver Test List

- [x] Successful Operation
- [x] Invalid Programming Voltage
- [x] Program error
- [x] Attempt to program protected block
- [x] Read back fails
- [x] Device timeout during write operation

</summary>
</details>

<details>
<summary>

## References

</summary>

* [CMock References](https://github.com/ThrowTheSwitch/CMock/blob/master/docs/CMock_Summary.md)

</details>