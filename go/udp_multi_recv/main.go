package main

import (
"net"
"log"
"time"
"runtime"
"bytes"
"strconv"
)

func GetGID() uint64 {
       b := make([]byte, 64)
       b = b[:runtime.Stack(b, false)]
       b = bytes.TrimPrefix(b, []byte("goroutine "))
       b = b[:bytes.IndexByte(b, ' ')]
       n, _ := strconv.ParseUint(string(b), 10, 64)
       return n
}

func recvUDPMsg(conn *net.UDPConn, port int) {

    gid := GetGID()

    log.Printf("port:%d,gid:%d\n", port, gid)

    var buf [1024]byte

    for {
    n, raddr, err := conn.ReadFromUDP(buf[0:])
    if err != nil {
        log.Printf("err:%+v\n", err)
        return
    }

    log.Printf("%d recv gid:%d, raddr:%+v,n:%d,buf:%+v\n", port, gid, raddr, n, buf[0:n])
    //time.Sleep(2 * time.Second)
    /*for i := 0; i < 3000000; i++ {
        n = 123
        }*/
    }
}

func main() {
    runtime.GOMAXPROCS(10)

    udp_addr, err := net.ResolveUDPAddr("udp", ":7012")
    if err != nil {
        log.Printf("err:%+v\n", err)
        return
    }

    {
        conn, err := net.ListenUDP("udp", udp_addr)
        if err != nil {
            log.Printf("err:%+v\n", err)
            return
        }
        defer conn.Close()

        go recvUDPMsg(conn, 701201)
    }

    {
        udp_addr, err := net.ResolveUDPAddr("udp", ":7012")
        if err != nil {
            log.Printf("err:%+v\n", err)
            return
        }

        conn, err := net.ListenUDP("udp", udp_addr)
        if err != nil {
            log.Printf("err:%+v\n", err)
            return
        }
        defer conn.Close()
        go recvUDPMsg(conn, 701202)
    }

    time.Sleep(10000000 * time.Second);

    log.Print("end!!!")
}

