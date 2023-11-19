import { Component, OnInit, OnDestroy } from '@angular/core';
import { UserType } from '../services/userType.service';
import { Subscription } from 'rxjs';

@Component({
  selector: 'app-account-info',
  templateUrl: './account-info.component.html',
  styleUrls: ['./account-info.component.css']
})

export class AccountInfoComponent {

  user!: string;
  private subscription!: Subscription;

  constructor(private userType: UserType) { }

  ngOnInit(): void {
    this.subscription = this.userType.currentAccountType.subscribe(
      (type: string) => {
        this.user = type;
      }
    );
    this.user = this.userType.getAccountType();
  }

  ngOnDestroy(): void {
    this.subscription.unsubscribe();
  }

  changeUserType(type: string): void {
    this.userType.changeAccountType(type);
  }
}