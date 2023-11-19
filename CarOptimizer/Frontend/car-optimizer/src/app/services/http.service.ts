import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class HttpService {
  constructor(private http: HttpClient) { }

  postCar(carData: any) {
    return this.http.post('http://localhost:8080/PostCar', carData, { responseType: 'text' });
  }
  

  getCar() {
    return this.http.get('http://localhost:8080/GetCar');
  }
}
