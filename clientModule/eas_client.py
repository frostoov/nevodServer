import asyncio


class EasClient:

    def __init__(self):
        self.control_client = _Client()
        self.data_client = _Client()
        self.queue = []
        self.id = 0

    def set_callback_functions(self, control_callback, data_callback):
        self.control_client.set_callback(control_callback)
        self.data_client.set_callback(data_callback)

    def connect_client_to_server(self, ip, control_port, data_port):
        self.control_client.connect_to(ip, control_port)
        # self.data_client.connect_to(ip, data_port)

    def connect_server_to_host(self, host_number,
                               host_ip=None):
        if host_ip is None:
            host_ip = "192.168.2.40"    # TODO
        rpc_json = self.__get_rpc_json("eas_connectToHost",
                                       [host_number, host_ip])
        self.queue.append(rpc_json)

    def disconnect_client_from_server(self):
        self.control_client.disconnect_from()
        self.data_client.disconnect_from()

    def disconnect_server_from_host(self, id_host):
        rpc_json = self.__get_rpc_json("eas_disconnectFromHost", [id_host])
        self.queue.append(rpc_json)

    def set_settings_configuration(self, name_of_configuration):
        rpc_json = self.__get_rpc_json("eas_setDefaultSettings",
                                       [name_of_configuration])
        self.queue.append(rpc_json)

    def set_threshold(self, id_paa, threshold):
        rpc_json = self.__get_rpc_json("eas_writeThreshold",
                                       [id_paa, threshold])
        self.queue.append(rpc_json)

    def set_thresholds_to_all(self, threshold):
        rpc_json = self.__get_rpc_json("eas_writeThresholdsToAll",
                                       [id_paa, threshold])
        self.queue.append(rpc_json)

    def set_coincidence(self, id_master, coincidence):
        rpc_json = self.__get_rpc_json("eas_writeThreshold",
                                       [id_master, coincidence])
        self.queue.append(rpc_json)

    def set_coincidence_to_all(self, coincidence):
        rpc_json = self.__get_rpc_json("eas_writeSetCoincidenceAll",
                                       [coincidence])
        self.queue.append(rpc_json)

    def hard_reset(self, id_master):
        rpc_json = self.__get_rpc_json("eas_writeHardReset", [id_master])
        self.queue.append(rpc_json)

    def start_work(self, id_paa, threshold):
        # TODO
        rpc_json = self.__get_rpc_json("eas_writeThreshold",
                                       [id_paa, threshold])
        self.queue.append(rpc_json)

    def allow_work_with_master(self, id_master, is_work=None):
        if is_work is None:
            is_work = True
        rpc_json = self.__get_rpc_json("eas_writePermissionOfMasters",
                                       [id_master, is_work])
        self.queue.append(rpc_json)

    def allow_work_with_host(self, id_host):
        rpc_json = self.__get_rpc_json("eas_writeRegisterOfReadData",
                                       [id_host])
        self.queue.append(rpc_json)

    def set_time_gate(srlf, id_master, nanoseconds):
        rpc_json = self.__get_rpc_json("eas_writeSetTimeGate",
                                       [id_master, nanoseconds])
        self.queue.append(rpc_json)

    def set_time_gate_to_all(self, nanoseconds):
        rpc_json = self.__get_rpc_json("eas_writeSetTimeGateToAll",
                                       [nanoseconds])
        self.queue.append(rpc_json)

    def set_task_table(self, id_host):
        rpc_json = self.__get_rpc_json("eas_writeThreshold",
                                       [id_paa, threshold])
        self.queue.append(rpc_json)

    def set_task_table_to_all(self):
        rpc_json = self.__get_rpc_json("eas_writeTaskTable", [])
        self.queue.append(rpc_json)

    def send_queue_to(self):
        for command in self.queue:
            self.control_client.send_to(command)
        self.id = 0

    def __get_rpc_json(self, name_of_method, list_of_arguments):
        rpc_json = {
            "jsonrpc": "2.0",
            "method": name_of_method,
            "params": list_of_arguments,
            "id": self.id
        }
        self.id += 1
        return rpc_json


class _Client:

    def __init__(self):
        pass

    def connect_to(self, ip, port):
        asyncio.ensure_future(self.__connect_to(ip, port))

    def send_to(self, msg):
        self.writer.write((str(msg) + "\n").encode("utf-8"))

    def disconnect_from(self):
        self.reader.close()
        self.writer.close()

    def start_read(self):
        future = asyncio.Future()
        asyncio.ensure_future(self.__receive_from(future))
        future.add_done_callback(self.__receive_from_callback)

    def set_callback(self, callback):
        self.callback = callback

    @asyncio.coroutine
    def __connect_to(self, ip, port):
        self.reader, self.writer = yield from asyncio.open_connection(ip, port)
        future = asyncio.Future()
        asyncio.ensure_future(self.__receive_from(future))
        future.add_done_callback(self.__receive_from_callback)

    @asyncio.coroutine
    def __send_to(self, msg):
        self.writer.write((msg + "\n").encode("utf-8"))

    @asyncio.coroutine
    def __receive_from(self, future):
        line = yield from self.reader.readline()
        future.set_result(line.decode("utf-8"))

    def __receive_from_callback(self, future):
        self.callback(future.result())

        future = asyncio.Future()
        asyncio.ensure_future(self.__receive_from(future))
        future.add_done_callback(self.__receive_from_callback)
