import { Component, OnInit } from '@angular/core';
import { HttpService } from '../services/http.service';
import { FormGroup, FormControl, Validators } from '@angular/forms';

@Component({
  selector: 'app-configure-car',
  templateUrl: './configure-car.component.html',
  styleUrls: ['./configure-car.component.css']
})
export class ConfigureCarComponent implements OnInit {
  carForm!: FormGroup;
  cars: any[] | null = null; 

  constructor(private httpService: HttpService) { }

  ngOnInit(): void {
    this.carForm = new FormGroup({
      make: new FormControl('', Validators.required),
      model: new FormControl('', Validators.required),
      year: new FormControl('', [Validators.required, Validators.pattern("^[0-9]*$")])
    });
  }

    //! this will create a car object for the user on the backend, which then can be used 
  //! to add parts and manipulate performance values 
  onSubmit() {
    if (this.carForm.valid) {
      this.httpService.postCar(this.carForm.value).subscribe(
        response => {
          console.log('Car data posted successfully', response);
          const jsonResponse = JSON.parse(response); // parse the response text to JSON
          console.log(jsonResponse);
        },
        error => {
          console.error('Error posting car data', error);
        }
      );
      
    }
  }


  //! this will grab database items and then need to put them in a dropdown 
  fetchCars() {
    this.httpService.getCar().subscribe(
      (data: any) => {
        this.cars = data; // Store the data in the component property
        console.log('Car data retrieved successfully', data);
      },
      (error) => {
        console.error('Error fetching car data', error);
        this.cars = []; // Reset the cars or handle the error appropriately
      }
    );
  }

}
