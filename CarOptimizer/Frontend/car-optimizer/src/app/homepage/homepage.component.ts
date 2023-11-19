import { Component } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'app-homepage',
  templateUrl: './homepage.component.html',
  styleUrls: ['./homepage.component.css']
})
export class HomepageComponent {

  constructor(
    private router: Router,
    ) {}

  redirectCarParts(): void {
    this.router.navigate(["parts"]);
  }

  redirectGallery(): void {
    this.router.navigate(["gallery"]);
  }

  redirectCarConfig(): void {
    this.router.navigate(["carConfig"]);
  }
}
